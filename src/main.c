/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:01:59 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/09 13:28:28 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	char	**ss;
	t_list	*dyn;
	size_t	i;

	dyn = NULL;
	str = readline("minishell>");
	if (!str)
		return (1);
	ss = lex(&dyn, str);
	if (!ss)
		return (1);
	i = 0;
	while (ss[i] != NULL)
	{
		ft_fprintf(STDOUT_FILENO, "%s\n", ss[i]);
		i++;
	}
	return (0);
}
