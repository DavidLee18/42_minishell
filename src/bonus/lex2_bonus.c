/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:33:49 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/26 02:19:31 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

size_t	lex_split(t_list **dyn, char **split, char const *s)
{
	size_t			i;
	t_split_piece	sp[3];
	ssize_t			next;

	i = 0;
	sp[1] = (t_split_piece){.start = -1, .length = -1};
	sp[2] = (t_split_piece){.start = 0, .length = 0};
	while (s[i])
	{
		next = lex_split_pos(s, i, sp);
		if (next > 0)
		{
			if (!lex_split_range(dyn, split, s, sp))
				return (0);
			sp[2].start = next;
			i = next;
		}
		else
			i++;
	}
	return (lex_split_final(dyn, split, s, sp));
}

size_t	lex_split_pos(const char *s, size_t i, t_split_piece *sp)
{
	if (s[i] == '\'')
	{
		sp->start = sp[2].start;
		sp->length = i - sp[2].start;
		sp[1].start = i;
		while (s[++i] != '\'')
			;
		sp[1].length = i + 1 - sp[1].start;
		return (i + 1);
	}
	else if (s[i] == '\"')
	{
		sp->start = sp[2].start;
		sp->length = i - sp[2].start;
		sp[1].start = i;
		while (s[++i] != '\"')
			;
		sp[1].length = i + 1 - sp[1].start;
		return (i + 1);
	}
	else
		return (lex_split_pos2(s, i, sp));
}

size_t	lex_split_pos2(const char *s, size_t i, t_split_piece *sp)
{
	if (ft_strncmp(s + i, ">>", 2) == 0 || ft_strncmp(s + i, "<<", 2) == 0
		|| ft_strncmp(s + i, "&&", 2) == 0 || ft_strncmp(s + i, "||", 2) == 0)
	{
		sp->start = sp[2].start;
		sp->length = i - sp[2].start;
		sp[1].start = i;
		sp[1].length = 2;
		return (i + 2);
	}
	else if (s[i] == '<' || s[i] == '|' || s[i] == '>' || s[i] == '('
		|| s[i] == ')')
	{
		sp->start = sp[2].start;
		sp->length = i - sp[2].start;
		sp[1].start = i;
		sp[1].length = 1;
		return (i + 1);
	}
	else if (is_space(s[i]))
	{
		sp->start = sp[2].start;
		sp->length = i - sp[2].start;
		return (i + 1);
	}
	return (0);
}

size_t	lex_split_final(t_list **dyn, char **split, char const *s,
			t_split_piece *sp)
{
	sp->start = sp[2].start;
	sp->length = ft_strlen(s) - sp[2].start;
	if (!lex_split_range(dyn, split, s, sp))
		return (0);
	return (sp[2].length);
}
