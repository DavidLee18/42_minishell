/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 00:19:58 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/15 00:30:25 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_pipes(t_phrase *p, t_pipe_rw *io, _Bool all)
{
	if (!io || all)
		(close(p->deb.pipe_ends.read_end),
			close(p->deb.pipe_ends.write_end));
	else
	{
		if (p->deb.pipe_ends.read_end > 2
			&& p->deb.pipe_ends.read_end != io->read_end
			&& p->deb.pipe_ends.read_end != io->write_end)
			close(p->deb.pipe_ends.read_end);
		if ((p->deb.pipe_ends.write_end > 2 && p->deb.pipe_ends.write_end
				!= io->read_end && p->deb.pipe_ends.write_end
				!= io->write_end))
			close(p->deb.pipe_ends.write_end);
	}
}
