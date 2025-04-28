/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:25:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/29 02:26:37 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	builtin_needs_swap(const char *str)
{
	return (ft_strcmp((char *)str, "cd") == 0
		|| ft_strcmp((char *)str, "export") == 0
		|| ft_strcmp((char *)str, "unset") == 0
		|| ft_strcmp((char *)str, "exit") == 0);
}

size_t	pipe_cnt(t_phrase *p)
{
	if (!p)
		return (0);
	if (p->type == PIPE)
		return (1 + pipe_cnt(p->succ));
	return (pipe_cnt(p->succ));
}

_Bool	validate_cmd(t_list **dyn, const char **envp, char **cmd)
{
	if (!ft_strchr(*cmd, '/'))
	{
		if (!get_exec_path(dyn, envp, *cmd))
			return (0);
		*cmd = get_exec_path(dyn, envp, *cmd);
		return (1);
	}
	else if (access(*cmd, F_OK) == 0)
	{
		if (access(*cmd, X_OK) == -1)
			return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
						*cmd)), 0);
		return (1);
	}
	return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
				*cmd)), 0);
}
