/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:27 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/24 23:47:17 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	lex_pre_meta_syll(const char *s, t_split_next *idxs, _Bool *syll)
{
	if (s[idxs->start] == '<' || s[idxs->start] == '|'
		|| s[idxs->start] == '>' || s[idxs->start] == '('
		|| s[idxs->start] == ')')
		idxs->length++;
	else if (*syll)
	{
		idxs->length++;
		*syll = 0;
	}
	else if (is_space(s[idxs->start]) && !is_space(s[idxs->start + 1]))
		*syll = 1;
}
