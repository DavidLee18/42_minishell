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

int			exec_builtin(char **argv, char **envp)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (exec_echo(argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd(argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (env(envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (exec_exit(argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (export(argv));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(argv));
	return (-1);
}
int			exec_echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i])
	{
		if (i == 1 && ft_strcmp(argv[i], "-n") == 0)
			flag = i++;
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
	char	*cwd;

	(void)argv;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int			env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
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
