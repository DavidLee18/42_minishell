/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:45:45 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/30 11:50:13 by jaehylee         ###   ########.fr       */
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
		sent = parse(dyn, tokens + 1);
		if (!sent)
			return (-1);
		temp = cons_and(dyn, phrase_head(*p), phrase_head(sent));
		if (temp == NULL)
			return (-1);
		*p = temp;
		i = 1;
		while (tokens[i])
			i++;
		return (i);
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
		sent = parse(dyn, tokens + 1);
		if (!sent)
			return (-1);
		temp = cons_or(dyn, phrase_head(*p), phrase_head(sent));
		if (temp == NULL)
			return (-1);
		*p = temp;
		i = 1;
		while (tokens[i])
			i++;
		return (i);
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
	p1 = parse(dyn, (const char **)ss);
	if (!p1)
		return (-1);
	(*p)->succ = phrase_head(p1);
	(*p)->succ->pred = *p;
	*p = (*p)->succ;
	i = 1;
	while (ss[i])
		i++;
	return (i + 2);
}
