/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:01:59 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/13 11:33:37 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_signal = 0;

int	main(void)
{
	char		*str;
	t_list		*dyn;
	t_phrase	*ps;

	dyn = NULL;
	if (!handle_signals())
		return (gc_free_all(dyn), 1);
	while (1)
	{
		str = prompt(&dyn);
		ps = parse_lex(&dyn, str);
		if (!ps)
			ft_fprintf(STDERR_FILENO, "failed to parse: `%s`\n", str);
		else
			print_phrase(ps);
	}
}
