/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:24:18 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/07 12:03:32 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

_Bool	builtin_needs_swap(const char *str)
{
	return (ft_strcmp((char *)str, "cd") == 0
		|| ft_strcmp((char *)str, "export") == 0
		|| ft_strcmp((char *)str, "unset") == 0
		|| ft_strcmp((char *)str, "exit") == 0);
}

char	**subparen(t_list **dyn, const char **tokens)
{
	size_t	parens;
	size_t	i;

	parens = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp((char *)tokens[i], "(") == 0)
			parens++;
		else if (ft_strcmp((char *)tokens[i], ")") == 0)
			parens--;
		if (parens == 0)
			break ;
		i++;
	}
	if (!tokens[i] && parens > 0)
		return (NULL);
	return (substrstr(dyn, tokens, 1, i - 1));
}

char	**substrstr(t_list **dyn, const char **tokens, size_t start, size_t len)
{
	char	**ss;
	size_t	i;

	if (len == 0)
		return (NULL);
	ss = (char **)gc_calloc(dyn, len + 1, sizeof(char *));
	if (!ss)
		return (NULL);
	i = start;
	while (i < start + len)
	{
		ss[i - start] = (char *)tokens[i];
		i++;
	}
	ss[i - start] = NULL;
	return (ss);
}

void	print_tabs(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_fprintf(STDOUT_FILENO, "\t");
		i++;
	}
}

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
