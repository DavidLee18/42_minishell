/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:08:49 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/16 13:32:05 by jaehylee         ###   ########.fr       */
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

void	decree_export(t_list **dyn, char **argv);
void	decree_unset(t_list **dyn, char **argv);
