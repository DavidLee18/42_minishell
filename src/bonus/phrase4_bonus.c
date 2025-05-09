/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase4_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:53:22 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/09 21:16:02 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_phrase	*next_branch(t_phrase *p)
{
	if (p->deb.tree.p1)
		return (close_branch_fps(phrase_head(p->deb.tree.p1)), p->deb.tree.p1);
	close_fps_all(phrase_head(p->deb.tree.p2));
	close_fps_all(phrase_head(p));
	return (p->deb.tree.p2);
}

_Bool	contains_comb_glob(t_phrase *p)
{
	if (!p)
		return (0);
	if (p->type == AND_COMB || p->type == OR_COMB)
		return (1);
	return (contains_comb_glob(p->succ));
}
