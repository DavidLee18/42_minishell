/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:30:22 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/13 19:44:57 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(const char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		ft_fprintf(STDOUT_FILENO, "%s ", args[i]);
		i++;
	}
	ft_fprintf(STDOUT_FILENO, "\n");
}

void	print_pipe(t_phrase *p)
{
	ft_fprintf(STDOUT_FILENO, "PIPE: read_end: %d, write_end: %d\n",
		p->deb.pipe_ends.read_end, p->deb.pipe_ends.write_end);
}
