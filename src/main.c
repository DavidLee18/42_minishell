/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:01:59 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/12 22:04:20 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(void)
{
	char		*str;
	t_list		*dyn;
	t_phrase	*ps;

	dyn = NULL;
	g_signal = 0;
	if (!handle_signals())
		return (gc_free_all(dyn), 1);
	while (1)
	{
		str = prompt(&dyn);
		if (!str)
			return (ft_fprintf(STDOUT_FILENO, "exit\n"), gc_free_all(dyn), 0);
		gc_add_to_list(&dyn, str);
		add_history(str);
		ps = parse_lex(&dyn, str);
		if (!ps)
		{
			ft_fprintf(STDERR_FILENO, "failed to parse: `%s`\n", str);
			continue ;
		}
		print_phrase(ps);
	}
	return (gc_free_all(dyn), 0);
}
