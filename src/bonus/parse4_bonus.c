/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:45:45 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/29 05:52:55 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

ssize_t	parse_and(t_list **dyn, t_phrase **p, const char **tokens)
{
	t_phrase	*sent;
	ssize_t		i;

	sent = NULL;
	if ((*p)->type != AND_COMB && (*p)->type != OR_COMB)
	{
		i = parse_each(dyn, &sent, tokens + 1);
		if (i <= 0)
			return (i);
		*p = cons_and(dyn, phrase_head(*p), phrase_head(sent));
		if (*p == NULL)
			return (-1);
		return (i + 1);
	}
	sent = (*p)->deb.tree.p2;
	i = parse_and(dyn, &((*p)->deb.tree.p2), tokens + 1);
	if (i < 0)
		return (i);
	return (i + 1);
}

ssize_t	parse_or(t_list **dyn, t_phrase **p, const char **tokens)
{
	t_phrase	*sent;
	ssize_t		i;

	if (!(*s) || ((*s)->comb == NOCOMB && (*s)->clause.p == NULL))
		return (-1);
	sent = NULL;
	if ((*s)->comb == NOCOMB)
	{
		i = parse_each(dyn, &sent, tokens + 1);
		if (i < 0)
			return (i);
		*s = cons_or(dyn, *s, sent);
		if (*s == NULL)
			return (-1);
		return (i + 1);
	}
	sent = (*s)->clause.s + 1;
	i = parse_and(dyn, &sent, tokens + 1);
	if (i < 0)
		return (i);
	return (i + 1);
}

ssize_t	parse_paren(t_list **dyn, t_phrase **p, const char **tokens)
{
}
