/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:12:15 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/07 11:58:38 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

_Bool	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

_Bool	is_cmd(const char *str)
{
	return (ft_strcmp((char *)str, "<") && ft_strcmp((char *)str, ">")
		&& ft_strcmp((char *)str, "<<") && ft_strcmp((char *)str, ">>")
		&& ft_strcmp((char *)str, "|") && ft_strcmp((char *)str, "&&")
		&& ft_strcmp((char *)str, "||"));
}

_Bool	is_builtin(const char *str)
{
	return (ft_strcmp((char *)str, "echo") == 0
		|| ft_strcmp((char *)str, "cd") == 0
		|| ft_strcmp((char *)str, "pwd") == 0
		|| ft_strcmp((char *)str, "export") == 0
		|| ft_strcmp((char *)str, "unset") == 0
		|| ft_strcmp((char *)str, "env") == 0
		|| ft_strcmp((char *)str, "exit") == 0);
}

void	print_args(const char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		ft_fprintf(STDOUT_FILENO, "%s ", args[i]);
		i++;
	}
	ft_fprintf(STDOUT_FILENO, "\n");
}

void	here_doc_prompt(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_fprintf(STDOUT_FILENO, ">");
		i++;
	}
	ft_fprintf(STDOUT_FILENO, " ");
}
