/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:08:49 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/26 22:46:19 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decree_cd(t_list **dyn, char **argv)
{
	int	ecode;

	if (!argv || !argv[0])
		return ;
	if (!argv[1])
		ecode = chdir(getenv("PATH"));
	else if (argv[2])
	{
		ft_fprintf(STDERR_FILENO, "%s: cd: too many arguments\n", MINISHELL);
		g_exit_status = 1;
		return ;
	}
	else
		ecode = chdir(getenv(argv[1]));
	g_exit_status = (-1) * ecode;
	if (ecode == -1)
		perror(gc_strjoin(dyn, MINISHELL, ": cd"));
}

void	decree_exit(t_list **dyn, char **argv)
{
	if (!argv || !argv[0])
		return ;
	ft_fprintf(STDOUT_FILENO, "exit\n");
	if (!argv[1])
		(gc_free_all(*dyn), exit(g_exit_status));
	else if (argv[2])
	{
		ft_fprintf(STDERR_FILENO, "%s: exit: too many arguments\n", MINISHELL);
		g_exit_status = 1;
		return ;
	}
	else
		(gc_free_all(*dyn), exit(ft_atoi(argv[1])));
}

void	declare_join(t_list **dyn, char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		(*envp)[i] = gc_strjoin(dyn, "declare -x", (*envp)[i]);
		i++;
	}
}

void	decree_export(t_list **dyn, char **argv, char ***envp)
{
	int		i;
	int		check;
	char	**str;
	char	**temp_av;

	declare_join(dyn, envp);
	if (argv[1] == NULL)
		print_env(*envp);
	i = 0;
	check = 0;
	temp_av = gc_split(dyn, argv[1], '=');
	while ((*envp)[i])
	{
		str = gc_split(dyn, (*envp)[i], '=');
		if ((ft_strcmp(temp_av[0], str[0]) == 0)
			&& (ft_strchr(argv[1], '=') != NULL))
		{
			(*envp)[i] = argv[1];
			check = 1;
			break ;
		}
		i++;
	}
	if ((check == 0) && (ft_strchr(argv[1], '=') != NULL))
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
