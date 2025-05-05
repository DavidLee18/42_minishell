/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 00:59:22 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/06 00:11:03 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*dyn;
	t_phrase	*ps;
	t_vec		pids;
	char		**env;

	dyn = NULL;
	pids = (t_vec){.cap = 0, .len = 0, .ptr = NULL};
	if (!handle_signals())
		return (gc_free_all(dyn), EXIT_FAILURE);
	env = env_copy(&dyn, envp);
	while (1)
	{
		str = prompt(&dyn);
		ps = parse_lex(&dyn, (const char **)env, str);
		if (!is_valid(phrase_head(ps), str))
			continue ;
		if (argc == 2 && ft_strcmp(argv[1], "--debug")
			== 0)
			(free(str), print_phrase(phrase_head(ps), 0),
				close_fps_all(phrase_head(ps)));
		else if (*str)
			(free(str), process(&dyn, phrase_head(ps), env, &pids),
				close_wait(&dyn, phrase_head(ps), &pids, &env));
	}
}
