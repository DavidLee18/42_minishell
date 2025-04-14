/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:48:27 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/15 04:09:22 by jaehylee         ###   ########.fr       */
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
			exit(EXIT_FAILURE), NULL);
	prom = readline(prom);
	if (!prom)
		return (ft_fprintf(STDOUT_FILENO, "exit\n"), gc_free_all(*dyn),
			free(prom), exit(EXIT_SUCCESS), NULL);
	add_history(prom);
	return (prom);
}

_Bool	handle_signals(void)
{
	struct sigaction	act;
	struct termios		term;
	int					ttyf;

	ft_bzero(&act, sizeof(act));
	ft_bzero(&term, sizeof(term));
	act.sa_handler = &set_signal;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (0);
	ttyf = open("/dev/tty", O_RDWR);
	if (ttyf == -1 || tcgetattr(ttyf, &term) == -1)
		return (perror(MINISHELL), 0);
	return (1);
}

void	set_signal(int s)
{
	if (s == SIGINT)
	{
		if (g_exit_status >= 0)
		{
			rl_replace_line("", 0);
			ft_fprintf(STDOUT_FILENO, "\n");
			rl_on_new_line();
			rl_redisplay();
		}
		else
			(kill(-g_exit_status, SIGINT), ft_fprintf(STDOUT_FILENO, "\n"));
		g_exit_status = 130;
	}
	else if (s == SIGQUIT)
	{
		if (g_exit_status >= 0)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			(kill(-g_exit_status, SIGQUIT), ft_fprintf(STDOUT_FILENO,
					"Quit (core dumped)\n"));
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
