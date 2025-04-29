/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:25:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/30 02:41:18 by jaehylee         ###   ########.fr       */
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

char	**get_cmd(t_phrase *p)
{
	char	**argv;

	argv = NULL;
	while (1)
	{
		while (p && p->type != NORMAL && p->type != BUILTIN && p->type != PIPE)
			p = p->succ;
		if (!p || p->type == PIPE)
			return (argv);
		else if (p->type != NORMAL && p->type != BUILTIN)
			p = p->succ;
		else if (argv == NULL)
		{
			argv = p->deb.argv;
			p = p->succ;
		}
		else
			return (NULL);
	}
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
	return (substrstr(dyn, tokens, 0, i + 1));
}

t_phrase	*cons_and(t_list **dyn, t_phrase *s1, t_phrase *s2)
{
	t_phrase	*p;

	if (!s1 || !s2)
		return (NULL);
	p = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
	if (!p)
		return (NULL);
	p->type = AND_COMB;
	p->deb.tree.p1 = s1;
	p->deb.tree.p2 = s2;
	p->pred = s1->pred;
	s1->pred = NULL;
	return (p);
}

t_phrase	*cons_or(t_list **dyn, t_phrase *s1, t_phrase *s2)
{
	t_phrase	*p;

	if (!s1 || !s2)
		return (NULL);
	p = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
	if (!p)
		return (NULL);
	p->type = OR_COMB;
	p->deb.tree.p1 = s1;
	p->deb.tree.p2 = s2;
	return (p);
}
