/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:31:29 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/26 22:40:09 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char **argv)
{
	int	i;

	i = 1;
	printf("export");
	while (argv[i])
	{
		printf(" %s", argv[i]);
		i++;
	}
	printf("\n");
	return (0);
}

int	unset(char **argv)
{
	int	i;

	i = 1;
	printf("unset");
	while (argv[i])
	{
		printf(" %s", argv[i]);
		i++;
	}
	printf("\n");
	return (0);
}

int	exec_exit(char **argv)
{
	int	i;

	i = 1;
	printf("exit");
	while (argv[i])
	{
		printf(" %s", argv[i]);
		i++;
	}
	printf("\n");
	return (0);
}
