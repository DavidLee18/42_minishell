/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:16:04 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/23 23:13:29 by jaehylee         ###   ########.fr       */
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

void	process_comb(t_list **dyn, t_phrase **p, char **envp, t_vec *pids)
{
	t_pipe_rw	io;

	io = get_io(p);
	while (p && *p && (*p)->type != PIPE)
	{
		switch_fds(dyn, *p, envp, &io);
		if (!(*p)->succ)
			break ;
		*p = (*p)->succ;
	}
	if (p && *p && (*p)->type == PIPE && io.write_end == STDOUT_FILENO)
		io.write_end = (*p)->deb.pipe_ends.write_end;
	push_front(dyn, pids, subshell(dyn, (t_phrase *[]){(*p), phrase_head(*p)},
			envp, &io));
	if (p && *p && ((*p)->type == PIPE || (*p)->succ))
		process(dyn, *p, envp, pids);
}

void	switch_fds(t_list **dyn, t_phrase *p, char **envp, t_pipe_rw *io)
{
	if (p->type == REDIR_IN)
		io->read_end = p->deb.fd;
	else if (p->type == REDIR_OUT || p->type == REDIR_APND)
		io->write_end = p->deb.fd;
	else if (p->type == HERE_DOC)
		io->read_end = here_doc(dyn, (const char **)envp,
				&p, count_here_docs(p));
}

void	close_fps_sub(t_phrase *parent, t_phrase *child_head,
	t_phrase *child_last)
{
	if (!parent || !child_head || !child_last)
		return ;
	if (child_head && parent == child_head)
	{
		if (child_head != child_last)
			close(child_head->deb.pipe_ends.write_end);
		while (parent && parent != child_last)
			parent = parent->succ;
		if (child_head != child_last)
			close(child_last->deb.pipe_ends.read_end);
		close_fps_all(parent->succ);
	}
	else if (parent->type == REDIR_IN || parent->type == REDIR_OUT
		|| parent->type == REDIR_APND)
		close(parent->deb.fd);
	else if (parent->type == PIPE)
		(close(parent->deb.pipe_ends.write_end),
			close(parent->deb.pipe_ends.read_end));
	else if (parent->type == AND_COMB || parent->type == OR_COMB)
		(close_fps_sub(parent->deb.tree.p1, child_head, child_last),
			close_fps_sub(parent->deb.tree.p2, child_head, child_last));
	if (parent->succ)
		close_fps_sub(parent->succ, child_head, child_last);
}
