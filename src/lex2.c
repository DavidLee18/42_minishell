/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:52:01 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/08 05:16:06 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	lex_split(t_list **dyn, char **split, char const *s)
{
	ssize_t			i;
	t_split_next	sp[2];
	t_quote			q;

	i = -1;
	q = NONE;
	sp[1] = (t_split_next){.start = 0, .length = 0};
	while (s[++i])
	{
		if ((s[i] == '\'' && q != DOUBLE) || (s[i] == '\"' && q != SINGLE)
			|| ft_strncmp(s + i, "<<", 2) == 0
			|| ft_strncmp(s + i, ">>", 2) == 0 || s[i] == '<' || s[i] == '|'
			|| s[i] == '>' || is_space(s[i]))
		{
			sp->start = sp[1].start;
			sp->length = i - sp[1].start;
			if ((size_t)i < sp[1].start || !lex_split_range(dyn, split, s, sp))
				return (0);
			sp[1].start = i + 1;
		}
	}
	return (1);
}
