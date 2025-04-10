/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:55:38 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/11 01:02:48 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	parse_cmd_builtin(t_list **dyn, t_phrase **p, const char **tokens,
			size_t *i)
{
	char	*cmd;

	if (!phrase_spawn(dyn, p) || tokens[*i] == NULL)
		return (0);
	cmd = unquote(tokens[(*i)++]);
	if (!cmd)
		return (0);
	if (is_builtin(cmd))
		(*p)->type = BUILTIN;
	else
		(*p)->type = NORMAL;
	(*p)->deb.argv = parse_split_args(dyn, tokens, i);
	if ((*p)->deb.argv == NULL)
		return (0);
	return (1);
}
