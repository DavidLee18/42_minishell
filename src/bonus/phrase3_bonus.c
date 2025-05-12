/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:57:33 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/07 14:03:17 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

_Bool	contains_comb(t_phrase *p)
{
	while (p && p->type != PIPE)
	{
		if (p->type == AND_COMB || p->type == OR_COMB)
			return (1);
		p = p->succ;
	}
	return (0);
}

t_phrase	*phrase_last(t_phrase *p)
{
	if (!p || !p->succ)
		return (p);
	return (phrase_head(p->succ));
}

t_phrase	*last_pipe(t_phrase *p)
{
	if (!p)
		return (NULL);
	if (p->type == PIPE)
		return (p);
	if (p->pred)
		return (last_pipe(p->pred));
	return (NULL);
}

t_phrase	*push_phrase_front(t_list **dyn, t_phrase *p, t_phrase *p2)
{
	t_phrase	*res;

	res = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
	if (!res)
		return (p2);
	res->type = p->type;
	res->deb = p->deb;
	res->pred = NULL;
	res->succ = p2;
	p2->pred = res;
	return (res);
}

t_phrase	*push_phrase_back(t_list **dyn, t_phrase *p, t_phrase *p2)
{
	t_phrase	*res;

	res = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
	if (!res)
		return (p2);
	res->type = p->type;
	res->deb = p->deb;
	res->succ = NULL;
	res->pred = p2;
	p2->succ = res;
	return (res);
}
