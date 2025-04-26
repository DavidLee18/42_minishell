/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:45:45 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/26 16:48:01 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

ssize_t	parse_and(t_list **dyn, t_sentence **s, const char **tokens)
{
	t_sentence	*sent;

	if ((*s)->comb == NOCOMB)
}

ssize_t		parse_or(t_list **dyn, t_sentence **s, const char **tokens);
ssize_t		parse_paren(t_list **dyn, t_sentence **s, const char **tokens,
			ssize_t *parens);
