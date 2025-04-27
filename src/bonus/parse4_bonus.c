/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:45:45 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/28 06:45:01 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

ssize_t	parse_and(t_list **dyn, t_sentence **s, const char **tokens,
	ssize_t *parens)
{
	t_sentence	*sent;
	ssize_t		i;

	sent = NULL;
	if ((*s)->comb == NOCOMB)
	{
		i = parse_each(dyn, &sent, tokens + 1, parens);
		if (i < 0)
			return (i);
		*s = cons_and(dyn, *s, sent);
		if (*s == NULL)
			return (-1);
		return (i + 1);
	}
	sent = (*s)->clause.s + 1;
	i = parse_and(dyn, &sent, tokens + 1, parens);
	if (i < 0)
		return (i);
	return (i + 1);
}

ssize_t	parse_or(t_list **dyn, t_sentence **s, const char **tokens,
			ssize_t *parens)
{
	t_sentence	*sent;
	ssize_t		i;

	if (!(*s) || ((*s)->comb == NOCOMB && (*s)->clause.p == NULL))
		return (-1);
	sent = NULL;
	if ((*s)->comb == NOCOMB)
	{
		i = parse_each(dyn, &sent, tokens + 1, parens);
		if (i < 0)
			return (i);
		*s = cons_or(dyn, *s, sent);
		if (*s == NULL)
			return (-1);
		return (i + 1);
	}
	sent = (*s)->clause.s + 1;
	i = parse_and(dyn, &sent, tokens + 1, parens);
	if (i < 0)
		return (i);
	return (i + 1);
}

ssize_t	parse_paren(t_list **dyn, t_sentence **s, const char **tokens,
			ssize_t *parens)
{
}
