/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:52:01 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/09 03:49:37 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	lex_split(t_list **dyn, char **split, char const *s)
{
	size_t			i;
	t_split_piece	sp[3];
	t_quote			q;
	ssize_t			next;

	i = 0;
	q = NONE;
	sp[1] = (t_split_piece){.start = -1, .length = -1};
	while (s[i])
	{
		next = lex_split_pos(s, i, sp, &q);
		if (next > 0)
		{
			if (!lex_split_range(dyn, split, s, sp))
				return (0);
			sp[1].start = next;
			i = next;
		}
		else
			i++;
	}
	return (1);
}

ssize_t	lex_split_pos(const char *s, size_t i, t_split_piece *sp, t_quote *q)
{
	if ((s[i] == '\'' && *q != DOUBLE) || (s[i] == '\"' && *q != SINGLE))
	{
		sp->start = sp[1].start;
		sp->length = i - sp[1].start + ((s[i] == '\'' && *q == SINGLE)
				|| (s[i] == '\"' && *q == DOUBLE));
		return (sp->start + sp->length);
	}
	else if (ft_strncmp(s + i, ">>", 2) == 0 || ft_strncmp(s + i, "<<", 2))
	{
		sp->start = sp[1].start;
		sp->length = i - sp[1].start;
		sp[1].start = i;
		sp[1].length = 2;
		return (i + 2);
	}
	else if (s[i] == '<' || s[i] == '|' || s[i] == '>')
	{
		sp->start = sp[1].start;
		sp->length = i - sp[1].start;
		sp[1].start = i;
		sp[1].length = 1;
		return (i + 1);
	}
}
