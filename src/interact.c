/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:48:27 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/12 15:10:19 by jaehylee         ###   ########.fr       */
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

_Bool	handle_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &set_signal;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (0);
	return (1);
}

void	set_signal(int s)
{
	g_signal = s;
	if (s == SIGINT)
	{
		rl_replace_line("", 0);
		ft_fprintf(STDOUT_FILENO, "\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (s == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
