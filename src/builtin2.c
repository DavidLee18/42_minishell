/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:08:49 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 02:02:22 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decree_cd(t_list **dyn, char **argv, const char **envp)
{
	int	ecode;

	if (!argv || !argv[0])
		return ;
	if (!argv[1])
		ecode = chdir(ft_get_env(dyn, envp, "HOME"));
	else if (argv[2])
	{
		ft_fprintf(STDERR_FILENO, "%s: cd: too many arguments\n", MINISHELL);
		g_exit_status = 1;
		return ;
	}
	else
		ecode = chdir(argv[1]);
	g_exit_status = (-1) * ecode;
	if (ecode == -1)
		perror(gc_strjoin(dyn, MINISHELL, ": cd"));
}

void	decree_exit(t_list **dyn, char **argv, int exit_code)
{
	if (!argv || !argv[0])
		return ;
	ft_fprintf(STDOUT_FILENO, "exit\n");
	if (!argv[1])
		(gc_free_all(*dyn), exit(exit_code));
	else if (argv[2])
	{
		ft_fprintf(STDERR_FILENO, "%s: exit: too many arguments\n", MINISHELL);
		g_exit_status = 1;
		return ;
	}
	else
	{
		exit_code = ft_atoi(argv[1]);
		(gc_free_all(*dyn), exit(exit_code));
	}
}

void	decree_export(t_list **dyn, char **argv, char ***envp)
{
	int		i;
	char	**str;
	char	**temp_av;

	if (argv[1] == NULL)
		return (export_print(dyn, *envp));
	i = 0;
	temp_av = gc_split(dyn, argv[1], '=');
	if (!temp_av || !temp_av[1])
		return ((void)ft_fprintf(STDERR_FILENO, "%s: export: why do you wanna"
				" export a variable without a value?\n", MINISHELL));
	while ((*envp)[i])
	{
		str = gc_split(dyn, (*envp)[i], '=');
		if (!ft_strcmp(temp_av[0], str[0]) && ft_strchr(argv[1], '='))
		{
			(*envp)[i] = ft_strchr(argv[1], '=') + 1;
			break ;
		}
		i++;
	}
	if ((*envp)[i] && ft_strchr(argv[1], '=')[1])
		reset_env(dyn, envp, argv[1]);
}

void	decree_unset(t_list **dyn, char **argv, char ***envp)
{
	int		i;
	char	**str;

	i = 0;
	while ((*envp)[i])
	{
		str = gc_split(dyn, (*envp)[i], '=');
		if ((ft_strcmp(argv[1], str[0]) == 0)
			&& (ft_strchr(argv[1], '=') == NULL))
		{
			(*envp)[i] = "";
			reset_env(dyn, envp, "");
			break ;
		}
		i++;
	}
}
