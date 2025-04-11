/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:48:27 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/12 05:21:43 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(t_list **dyn)
{
	char	*pwd;
	char	*prom;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	prom = gc_strjoin(dyn, gc_strjoin(dyn, "minishell:", pwd), "> ");
	free(pwd);
	if (!prom)
		return (NULL);
	return (readline(prom));
}

int	handle_signals(void)
{
	struct sigaction	act;

	act = (struct sigaction){.sa_handler = SIG_IGN};

	if (sigaction(SIGINT, &act, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (-1);
	return (0);
}
