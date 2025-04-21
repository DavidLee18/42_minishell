/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:01:59 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/21 12:07:22 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*dyn;
	t_phrase	*ps;
	t_vec		pids;

	dyn = NULL;
	pids = (t_vec){.cap = 0, .len = 0, .ptr = NULL};
	if (!handle_signals())
		return (gc_free_all(dyn), EXIT_FAILURE);
	while (1)
	{
		str = prompt(&dyn);
		ps = parse_lex(&dyn, str);
		if (!ps && *str)
			ft_fprintf(STDERR_FILENO, "failed to parse: `%s`\n", str);
		else if (argc == 2 && ft_strcmp(argv[1], "--debug") == 0)
			(free(str), print_phrase(ps), close_pipes(phrase_head(ps),
					NULL, 1));
		else if (*str)
		{
			free(str);
			process(&dyn, phrase_head(ps), envp, &pids);
			close_wait(&dyn, phrase_head(ps), &pids);
		}
	}
}
