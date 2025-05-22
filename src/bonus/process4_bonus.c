/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:16:04 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/22 21:19:45 by jaehylee         ###   ########.fr       */
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
		if ((*p)->type == REDIR_IN)
			io.read_end = (*p)->deb.fd;
		else if ((*p)->type == REDIR_OUT || (*p)->type == REDIR_APND)
			io.write_end = (*p)->deb.fd;
		else if ((*p)->type == HERE_DOC)
			io.read_end = here_doc(dyn, (const char **)envp,
					p, count_here_docs(*p));
		*p = (*p)->succ;
	}
	if (p && *p && (*p)->type == PIPE && io.write_end == STDOUT_FILENO)
		io.write_end = (*p)->deb.pipe_ends.write_end;
	push_front(dyn, pids, subshell(dyn, *p, envp, &io));
	if (p && *p && ((*p)->type == PIPE || (*p)->succ))
		process(dyn, *p, envp, pids);
}
