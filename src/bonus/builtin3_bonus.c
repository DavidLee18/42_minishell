/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:30:30 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 22:30:48 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
