/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc5_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:27:18 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 22:28:01 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

_Bool	validate_cmd(t_list **dyn, const char **envp, char **cmd)
{
	if (!ft_strchr(*cmd, '/'))
	{
		if (!get_exec_path(dyn, envp, *cmd))
		{
			g_exit_status = 127;
			return (0);
		}
		*cmd = get_exec_path(dyn, envp, *cmd);
		return (1);
	}
	else if (access(*cmd, F_OK) == 0)
	{
		if (access(*cmd, X_OK) == -1)
		{
			g_exit_status = 126;
			return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
						*cmd)), 0);
		}
		return (1);
	}
	g_exit_status = 127;
	return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
				*cmd)), 0);
}
