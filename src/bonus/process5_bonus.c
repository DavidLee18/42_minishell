/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process5_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:07:01 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/09 21:41:22 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	process_comb_branch(t_list **dyn, t_phrase *p[2], char **envp,
	t_vec *pids)
{
	t_pipe_rw	io;
	char		**argv;

	if (contains_comb(p[1]) || (p[1] && p[1]->type == PIPE
			&& contains_comb(p[1]->succ)))
		process_comb(dyn, p + 1, envp, pids);
	io = get_io(p + 1);
	argv = get_cmd(p[1]);
	if (argv == NULL)
		return ;
	while (p[1] && p[1]->type != PIPE)
	{
		if (p[1]->type == REDIR_IN)
			io.read_end = p[1]->deb.fd;
		else if (p[1]->type == REDIR_OUT || p[1]->type == REDIR_APND)
			io.write_end = p[1]->deb.fd;
		else if (p[1]->type == HERE_DOC)
			io.read_end = here_doc(dyn, (const char **)envp, p + 1,
					count_here_docs(p[1]));
		p[1] = p[1]->succ;
	}
	if (p[1] && p[1]->type == PIPE && io.write_end == STDOUT_FILENO)
		io.write_end = p[1]->deb.pipe_ends.write_end;
	push_front(dyn, pids, exec_branch(dyn, p, (char **[]){argv, envp}, &io));
	process_next_branch(dyn, p, envp, pids);
}

void	process_next_branch(t_list **dyn, t_phrase *p[2], char **envp,
	t_vec *pids)
{
	if (p[1] && (p[1]->type == PIPE || p[1]->succ))
		process_comb_branch(dyn, p, envp, pids);
}

int	exec_branch(t_list **dyn, t_phrase *p[2], char **arg_env[2],
	t_pipe_rw *io)
{
	int	id;

	(ignore_signals(), builtin_fd_swap(dyn, p[1], io));
	id = fork();
	if (id == -1)
		perror(gc_strjoin(dyn, MINISHELL, ": fork"));
	else if (id == 0)
	{
		(handle_signals_ch(), close_pipes(phrase_head(p[0]), io));
		dup_io(dyn, p[1], io);
		if (is_builtin(arg_env[0][0]))
		{
			close_io(io);
			id = exec_builtin(arg_env[0], arg_env[1]);
			(gc_free_all(*dyn), exit(id));
		}
		else
			(close_io(io), execve(arg_env[0][0], arg_env[0], arg_env[1]));
		(gc_free_all(*dyn), exit(EXIT_FAILURE));
	}
	return (id);
}

void	close_branch_fps(t_phrase *p)
{
	if (!p)
		return ;
	else if (p->type == REDIR_IN || p->type == REDIR_OUT
		|| p->type == REDIR_APND)
		close(p->deb.fd);
	else if (p->type == PIPE)
	{
		if (p->succ)
			close(p->deb.pipe_ends.write_end);
		if (p->pred)
			close(p->deb.pipe_ends.read_end);
	}
	if (p->succ)
		close_branch_fps(p->succ);
}

void	restore_pids(t_phrase *from, t_phrase *to, t_vec *pids)
{
	while (from && from->pred && to && pids && from != to)
	{
		from = from->pred;
		rotate_down(pids);
	}
}
