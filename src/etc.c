/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:03:34 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/11 01:17:09 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

_Bool	phrase_spawn(t_list **dyn, t_phrase **p)
{
	if (*p == NULL)
	{
		*p = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
		if (*p == NULL)
			return (0);
	}
	else
	{
		(*p)->succ = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
		if ((*p)->succ == NULL)
			return (0);
		(*p)->succ->pred = *p;
		*p = (*p)->succ;
	}
	return (1);
}

_Bool	is_cmd(const char *str)
{
	return (ft_strcmp((char *)str, "<") && ft_strcmp((char *)str, ">")
		&& ft_strcmp((char *)str, "<<") && ft_strcmp((char *)str, ">>")
		&& ft_strcmp((char *)str, "|"));
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
