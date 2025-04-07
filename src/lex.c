/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:45:12 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/08 05:16:35 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	lex_preproc(char const *s, t_split_next *idxs, t_quote *p, _Bool *syll)
{
	if (s[idxs->start] == '\0')
		return (0);
	if ((s[idxs->start] == '\'' && *p != DOUBLE)
		|| (s[idxs->start] == '\"' && *p != SINGLE))
		lex_pre_paren(s[idxs->start], idxs, p);
	else if ((s[idxs->start] == '<' && s[idxs->start + 1] == '<')
		|| (s[idxs->start] == '>' && s[idxs->start + 1] == '>'))
	{
		idxs->start++;
		idxs->length++;
	}
	else if (s[idxs->start] == '<' || s[idxs->start] == '|'
		|| s[idxs->start] == '>')
		idxs->length++;
	else if (*syll)
	{
		idxs->length++;
		*syll = 0;
	}
	else if (is_space(s[idxs->start]) && !is_space(s[idxs->start + 1]))
		*syll = 1;
	idxs->start++;
	return (1);
}

void	lex_pre_paren(char c, t_split_next *idxs, t_quote *p)
{
	if (c == '\'' && *p != DOUBLE)
	{
		*p = SINGLE - *p;
		if (*p == NONE)
			idxs->length++;
	}
	else if (c == '\"' && *p != SINGLE)
	{
		*p = DOUBLE - *p;
		if (*p == NONE)
			idxs->length++;
	}
}

char	**lex_alloc(t_list **dyn, char const *s)
{
	char			**split;
	t_quote			p;
	t_split_next	idxs;
	_Bool			syllable;

	idxs = (t_split_next){0, 0};
	p = NONE;
	syllable = 0;
	while (s[idxs.start])
		if (!lex_preproc(s, &idxs, &p, &syllable))
			return (NULL);
	if (p != NONE)
		return (NULL);
	split = (char **)gc_calloc(dyn, idxs.length + 2, sizeof(char *));
	if (!split)
		return (NULL);
	return (split);
}

char	**lex(t_list **dyn, const char *s)
{
	char	**split;

	split = lex_alloc(dyn, s);
	if (!split)
		return (NULL);
	if (!lex_split(dyn, split, s))
		return (NULL);
	return (split);
}

_Bool	lex_split_range(t_list **dyn, char **split, char const *s,
		t_split_next *sp)
{
	char	*str;

	str = gc_substr(dyn, s, sp->start, sp->length);
	if (!str)
		return (0);
	if (!*str)
		return (1);
	split[(sp + 1)->length] = str;
	(sp + 1)->length++;
	return (1);
}
