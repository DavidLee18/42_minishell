/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 00:59:22 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/25 04:00:05 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(void)
{
	char	*str;
	char	**tokens;
	t_list	*dyn;

	dyn = NULL;
	str = readline("minishell>");
	tokens = lex(&dyn, str);
	if (!tokens)
		return (1);
	while (tokens && *tokens)
	{
		ft_fprintf(STDOUT_FILENO, "%s\n", *tokens);
		tokens++;
	}
	return (0);
}
