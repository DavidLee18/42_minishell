/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:56:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/10 10:28:07 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_phrase	*parse(t_list **dyn, const char **tokens)
{
	size_t		i;
	t_phrase	*p;

	i = 0;
	p = NULL;
	while (tokens[i] != NULL)
	{
		if (ft_strcmp((char *)tokens[i], "<") == 0
			&& !parse_redir_in(dyn, &p, tokens, &i))
			return (NULL);
		if (ft_strcmp((char *)tokens[i], ">") == 0
			&& !parse_redir_out(dyn, &p, tokens, &i))
			return (NULL);
		if (ft_strcmp((char *)tokens[i], "<<") == 0
			&& !parse_here_doc(dyn, &p, tokens, &i))
			return (NULL);
		if (ft_strcmp((char *)tokens[i], ">>") == 0
			&& !parse_redir_apnd(dyn, &p, tokens, &i))
			return (NULL);
		if (!parse_cmd_builtin(dyn, &p, tokens, &i))
			return (NULL);
	}
	return (p);
}

_Bool	parse_redir_in(t_list **dyn, t_phrase **p, const char **tokens,
			size_t *i)
{
	if (*p == NULL)
	{
		*p = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
		if (*p == NULL)
			return (0);
	}
	else
	{
		(*p)->succ = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
		if ((*p)->succ == NULL)
			return (0);
		(*p)->succ->pred = *p;
		*p = (*p)->succ->pred;
	}
	(*i)++;
	// TODO
}
