/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:48:27 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/13 19:37:11 by jaehylee         ###   ########.fr       */
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
	pwd = NULL;
	if (!prom)
		return (ft_fprintf(STDERR_FILENO, "alloc Error"), gc_free_all(*dyn),
			exit(1), NULL);
	prom = readline(prom);
	if (!prom)
		return (ft_fprintf(STDOUT_FILENO, "exit\n"), gc_free_all(*dyn), exit(0),
			NULL);
	add_history(prom);
	return (prom);
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

t_phrase	*parse_lex(t_list **dyn, const char *str)
{
	char	**tokens;

	tokens = lex(dyn, str);
	if (!tokens)
		return (NULL);
	return (parse(dyn, (const char **)tokens));
}
