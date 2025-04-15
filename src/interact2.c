/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 02:22:50 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/16 02:24:34 by jaehylee         ###   ########.fr       */
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
