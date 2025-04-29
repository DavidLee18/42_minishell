/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:45:45 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/30 02:40:45 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

ssize_t	parse_and(t_list **dyn, t_phrase **p, const char **tokens)
{
	t_phrase	*sent;
	ssize_t		i;
	t_phrase	*temp;

	if (!(*p))
		return (-1);
	sent = NULL;
	if ((*p)->type != AND_COMB && (*p)->type != OR_COMB)
	{
		i = parse_each(dyn, &sent, tokens + 1);
		if (i <= 0)
			return (i);
		temp = phrase_head(*p);
		temp = cons_and(dyn, temp, phrase_head(sent));
		if (temp == NULL)
			return (-1);
		*p = temp;
		return (i + 1);
	}
	return (parse_and(dyn, &((*p)->deb.tree.p2), tokens));
}

ssize_t	parse_or(t_list **dyn, t_phrase **p, const char **tokens)
{
	t_phrase	*sent;
	ssize_t		i;
	t_phrase	*temp;

	if (!(*p))
		return (-1);
	sent = NULL;
	if ((*p)->type != AND_COMB && (*p)->type != OR_COMB)
	{
		i = parse_each(dyn, &sent, tokens + 1);
		if (i <= 0)
			return (i);
		temp = phrase_head(*p);
		temp = cons_or(dyn, temp, phrase_head(sent));
		if (temp == NULL)
			return (-1);
		*p = temp;
		return (i + 1);
	}
	return (parse_or(dyn, &((*p)->deb.tree.p2), tokens));
}

ssize_t	parse_paren(t_list **dyn, t_phrase **p, const char **tokens)
{
	t_phrase	*p1;
	char		**ss;
	ssize_t		i;

	if (ft_strcmp((char *)*tokens, ")") == 0)
		return (-1);
	p1 = NULL;
	ss = subparen(dyn, tokens);
	if (!ss)
		return (-1);
	i = parse_each(dyn, &p1, (const char **)ss);
	if (i <= 0)
		return (i);
	(*p)->succ = phrase_head(p1);
	return (i + 2);
}
