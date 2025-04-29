/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 00:59:22 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/30 02:25:21 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(void)
{
	char		*str;
	t_list		*dyn;
	t_phrase	*ps;

	dyn = NULL;
	while (1)
	{
		str = prompt(&dyn);
		ps = parse_lex(&dyn, str);
		if (!ps && *str)
			ft_fprintf(STDERR_FILENO, "failed to parse: `%s`\n", str);
		else
			(free(str), print_phrase(phrase_head(ps), 0),
				close_pipes(phrase_head(ps), NULL, 1));
	}
}
