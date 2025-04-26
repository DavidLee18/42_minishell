/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:25:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/26 00:33:33 by jaehylee         ###   ########.fr       */
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

_Bool	sentence_spawn(t_list **dyn, t_sentence **s)
{
	if (*s == NULL)
	{
		*s = (t_sentence *)gc_calloc(dyn, 1, sizeof(t_sentence));
		if (*s == NULL)
			return (0);
	}
	else
	{
		(*s)->next = (t_sentence *)gc_calloc(dyn, 1, sizeof(t_sentence));
		if ((*s)->next == NULL)
			return (0);
		(*s)->next->prev = *s;
		*s = (*s)->next;
	}
	return (1);
}
