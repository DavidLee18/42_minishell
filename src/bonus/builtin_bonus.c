/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:29:01 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 22:29:57 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	exec_builtin(char **argv, char **envp)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (exec_echo(argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd(argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (env(argv, envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (exec_exit(argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (export(argv));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(argv));
	return (-1);
}

int	exec_echo(char **argv)
{
	int	i;

	i = 1 + (ft_strcmp(argv[1], "-n") == 0);
	while (argv[i])
	{
		if (argv[1][0] == '-' && ft_strcmp(argv[1], "-n"))
			return (ft_fprintf(STDERR_FILENO, "%s: echo: unrecognized option "
					"`%s`\n", MINISHELL, argv[1]), 2);
		ft_fprintf(STDOUT_FILENO, "%s", argv[i]);
		if (argv[i + 1])
			ft_fprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (argv[1] && ft_strcmp(argv[1], "-n"))
		ft_fprintf(STDOUT_FILENO, "\n");
	return (0);
}

int	cd(char **argv)
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

int	pwd(char **argv)
{
	char	*cwd;

	if (argv[1] != NULL)
		return (ft_fprintf(STDERR_FILENO, "%s: pwd: too many arguments\n",
				MINISHELL), 2);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	env(char **argv, char **envp)
{
	int	i;

	if (argv[1] != NULL)
		return (ft_fprintf(STDERR_FILENO, "%s: env: too many arguments\n",
				MINISHELL), 2);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
