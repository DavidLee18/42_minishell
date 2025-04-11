/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:01:59 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/11 18:50:25 by jaehylee         ###   ########.fr       */
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
	str = readline("minishell> ");
	if (!str)
		return (1);
	tokens = lex(&dyn, str);
	if (!tokens)
		return (1);
	ps = parse(&dyn, (const char **)tokens);
	if (!ps)
		return (1);
	return (0);
}
