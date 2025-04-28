/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:25:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/28 16:59:01 by jaehylee         ###   ########.fr       */
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
