/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:01:59 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/12 17:41:49 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(void)
{
	char		*str;
	char		**tokens;
	t_list		*dyn;
	t_phrase	*ps;

	dyn = NULL;
	g_signal = 0;
	while (1)
	{
		if (!handle_signals())
			return (gc_free_all(dyn), 1);
		str = prompt(&dyn);
		if (!str)
			return (ft_fprintf(STDOUT_FILENO, "exit\n"), gc_free_all(dyn), 1);
		tokens = lex(&dyn, str);
		free(str);
		if (!tokens)
			continue ;
		ps = parse(&dyn, (const char **)tokens);
		if (!ps)
			continue ;
		print_phrase(ps);
	}
	return (gc_free_all(dyn), 0);
}
