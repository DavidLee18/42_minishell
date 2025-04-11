/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:01:59 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/12 05:43:51 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*str;
	char		**tokens;
	t_list		*dyn;
	t_phrase	*ps;

	dyn = NULL;
	if (handle_signals() == -1)
		return (1);
	while (1)
	{
		str = prompt(&dyn);
		if (!str)
			return (gc_free_all(dyn), 1);
		tokens = lex(&dyn, str);
		free(str);
		if (!tokens)
			return (gc_free_all(dyn), 1);
		ps = parse(&dyn, (const char **)tokens);
		if (!ps)
			return (gc_free_all(dyn), 1);
		print_phrase(ps);
	}
	return (gc_free_all(dyn), 0);
}
