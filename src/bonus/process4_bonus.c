/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:16:04 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/05 04:44:49 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	dup_io(t_list **dyn, t_phrase *p, t_pipe_rw *io)
{
	if (io->read_end == -1 || (io->read_end != STDIN_FILENO
			&& dup2(io->read_end, STDIN_FILENO) == -1))
		(close_pipes(phrase_head(p), NULL), gc_free_all(*dyn),
			exit(EXIT_FAILURE));
	if (io->write_end == -1 || (io->write_end != STDOUT_FILENO
			&& dup2(io->write_end, STDOUT_FILENO) == -1))
		(close_pipes(phrase_head(p), NULL), gc_free_all(*dyn),
			exit(EXIT_FAILURE));
}

void	process_comb(t_list **dyn, t_phrase *p, char **envp, t_vec *pids)
{
	while (p->type != AND_COMB && p->type != OR_COMB)
		p = p->succ;
	if (p->deb.tree.p1)
		process(dyn, p->deb.tree.p1, envp, pids);
	else
		process(dyn, p->deb.tree.p2, envp, pids);
}

void	wait_comb(t_list **dyn, t_phrase *p, t_vec *pids, char ***envp)
{
	while (p->type != AND_COMB && p->type != OR_COMB)
		p = p->succ;
	if (p->deb.tree.p1)
	{
		wait_comb_branch(dyn, p->deb.tree.p1, pids, envp);
		p->deb.tree.p1 = NULL;
		if ((p->type == AND_COMB && g_exit_status == 0)
			|| (p->type == OR_COMB && g_exit_status != 0))
			(process_comb(dyn, p, *envp, pids),
				wait_comb_branch(dyn, p, pids, envp));
	}
	else
		wait_comb_branch(dyn, p->deb.tree.p2, pids, envp);
}

void	wait_comb_branch(t_list **dyn, t_phrase *p, t_vec *pids, char ***envp)
{
	int	*id;
	int	stat;

	stat = 0;
	close_fps_all(p);
	id = pop_back(dyn, pids);
	p = p->succ;
	if (id && g_exit_status < -1)
		exec_builtin_message(dyn, -g_exit_status, *id, envp);
	while (id && p)
	{
		waitpid(*id, &stat, 0);
		if (WIFEXITED(stat))
			g_exit_status = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
		{
			g_exit_status = WTERMSIG(stat) + 128;
			if (WTERMSIG(stat) == SIGQUIT)
				ft_fprintf(STDOUT_FILENO, "Quit (core dumped)");
			ft_fprintf(STDOUT_FILENO, "\n");
		}
		id = pop_back(dyn, pids);
		p = p->succ;
	}
}
