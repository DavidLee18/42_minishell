/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:07:08 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/14 21:02:53 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// STDIN_FILENO read_end
// STDOUT_FILENO wirte_end

int			exec_builtin(char *name, char **argv)
{
	if (ft_strcmp(name, "echo") == 0)
		return (exec_echo(argv));
	else if (ft_strcmp(name, "cd") == 0)
		return (cd(argv));
	else if (ft_strcmp(name, "pwd") == 0)
		return (pwd(argv));
	else if (ft_strcmp(name, "exit") == 0)
		return (exec_exit(argv));
	else if (ft_strcmp(name, "export") == 0)
		return (export(argv));
	else if (ft_strcmp(name, "unset") == 0)
		return (unset(argv));
	return (-1);
}
int			exec_echo(char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[0], "-n") == 0)
			flag = 1;
		if (flag == 0 && !argv[i + 1])
		{
			printf("%s\n", argv[i]);
			break ;
		}
		else if (flag == 1 && !argv[i + 1])
		{
			printf("%s", argv[i]);
			break ;
		}
		printf("%s ", argv[i]);
		i++;
	}
	return (0);
}

int			cd(char **argv)
{
	int	i;

	i = 1;
	printf("cd");
	while (argv[i])
	{
		printf(" %s", argv[i]);
		i++;
	}
	printf("\n");
	return (0);
}

int			pwd(char **argv)
{
	if (getcwd(argv[0], ft_strlen(argv[0])) == NULL)
		return (1);
	printf("%s\n", argv[0]);
	return (0);
}

int			exec_exit(char **argv)
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

int		export(char **argv)
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

int		unset(char **argv)
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
//성공 0
//실패 1
//잘못된 인자 2