/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 02:22:50 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/16 07:21:53 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	ignore_signals(void)
{
	struct sigaction	act;
	sigset_t			masks;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&masks);
	sigaddset(&masks, SIGINT);
	sigaddset(&masks, SIGQUIT);
	act.sa_mask = masks;
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (0);
	return (1);
}

void	builtin_fd_swap(t_list **dyn, t_phrase *p, t_pipe_rw *io)
{
	int	fp[2];

	if (cmd_len(phrase_head(p)) != 1 || p->type != BUILTIN)
		return ;
	if (pipe(fp) == -1)
	{
		perror(gc_strjoin(dyn, MINISHELL, ": pipe"));
		return ;
	}
	io->write_end = fp[1];
	g_exit_status = -fp[0];
}
