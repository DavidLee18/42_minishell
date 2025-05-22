/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:39:18 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/23 06:45:42 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	process(t_list **dyn, t_phrase *p, char **envp, t_vec *pids)
{
	t_pipe_rw	io;
	char		**argv;

	if (contains_comb(p) || (p->type == PIPE && contains_comb(p->succ)))
		process_comb(dyn, &p, envp, pids);
	io = get_io(&p);
	argv = get_cmd(p);
	if (argv == NULL)
		return ;
	while (p && p->type != PIPE)
	{
		switch_fds(dyn, p, envp, &io);
		if (!p->succ)
			break ;
		p = p->succ;
	}
	if (p && p->type == PIPE && io.write_end == STDOUT_FILENO)
		io.write_end = p->deb.pipe_ends.write_end;
	push_front(dyn, pids, exec_cmd(dyn, p, (char **[]){argv, envp}, &io));
	if (p && (p->type == PIPE || p->succ))
		process(dyn, p, envp, pids);
}

pid_t	exec_cmd(t_list **dyn, t_phrase *p, char **arg_env[2], t_pipe_rw *io)
{
	pid_t	id;

	(ignore_signals(), builtin_fd_swap(dyn, p, io));
	id = fork();
	if (id == -1)
		perror(gc_strjoin(dyn, MINISHELL, ": fork"));
	else if (id == 0)
	{
		(handle_signals_ch(), close_pipes(phrase_head(p), io));
		dup_io(dyn, p, io);
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

char	**get_cmd(t_phrase *p)
{
	char	**argv;

	argv = NULL;
	while (1)
	{
		while (p && p->type != NORMAL && p->type != BUILTIN && p->type != PIPE)
			p = p->succ;
		if (!p || p->type == PIPE)
			return (argv);
		else if ((p->type == NORMAL || p->type == BUILTIN) && argv == NULL)
		{
			argv = p->deb.argv;
			p = p->succ;
		}
		else
			return (NULL);
	}
}

t_pipe_rw	get_io(t_phrase **p)
{
	t_pipe_rw	io;

	io = (t_pipe_rw){.read_end = STDIN_FILENO, .write_end = STDOUT_FILENO};
	if (!*p)
		return (io);
	if ((*p)->type != PIPE)
		return (io);
	io.read_end = (*p)->deb.pipe_ends.read_end;
	*p = (*p)->succ;
	return (io);
}

pid_t	subshell(t_list **dyn, t_phrase *ps[2], char **envp, t_pipe_rw *io)
{
	pid_t	id;
	t_vec	pids;

	ignore_signals();
	id = fork();
	if (id == -1)
		perror(gc_strjoin(dyn, MINISHELL, ": fork"));
	else if (id == 0)
	{
		close_fps_sub(ps[0], ps[1]);
		(dup_io(dyn, ps[1], io), close_io(io));
		while (ps[1] && ps[1]->type != AND_COMB && ps[1]->type != OR_COMB)
			ps[1] = ps[1]->pred;
		pids = (t_vec){.cap = 0, .len = 0, .ptr = NULL};
		process(dyn, ps[1]->deb.tree.p1, envp, &pids);
		close_wait(dyn, ps[1]->deb.tree.p1, &pids, &envp);
		if ((ps[1]->type == AND_COMB && g_exit_status == 0)
			|| (ps[1]->type == OR_COMB && g_exit_status != 0))
			(process(dyn, ps[1]->deb.tree.p2, envp, &pids),
				close_wait(dyn, ps[1]->deb.tree.p2, &pids, &envp));
		(gc_free_all(*dyn), exit(g_exit_status));
	}
	return (id);
}
