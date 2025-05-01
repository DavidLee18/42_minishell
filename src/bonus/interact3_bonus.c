/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:36:08 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 22:36:35 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

_Bool	heredoc_signals(void)
{
	struct sigaction	act;
	sigset_t			masks;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&masks);
	sigaddset(&masks, SIGINT);
	sigaddset(&masks, SIGQUIT);
	act.sa_mask = masks;
	act.sa_handler = &on_idle;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (0);
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (0);
	return (1);
}
