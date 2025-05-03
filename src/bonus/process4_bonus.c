/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:16:04 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/04 00:15:03 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	comb_rearr_io(t_list **dyn, t_phrase **p, char **envp, t_pipe_rw *io)
{
	t_phrase	*temp;

	if ((*p)->deb.tree.p1)
		temp = (*p)->deb.tree.p1;
	else
		temp = (*p)->deb.tree.p2;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIR_IN)
			io->read_end = temp->deb.fd;
		else if (temp->type == REDIR_OUT || temp->type == REDIR_APND)
			io->write_end = temp->deb.fd;
		else if (temp->type == HERE_DOC)
			io->read_end = here_doc(dyn, (const char **)envp,
					&temp, count_here_docs(temp));
		else if (temp->type == AND_COMB || temp->type == OR_COMB)
			comb_rearr_io(dyn, &temp, envp, io);
		temp = temp->succ;
	}
	if (temp && temp->type == PIPE)
		comb_rearr_io(dyn, &temp->succ, envp, io);
}
