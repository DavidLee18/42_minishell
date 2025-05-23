/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase4_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 23:20:35 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/23 23:24:28 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_phrase	*first_pipe_after(t_phrase *p)
{
	if (!p)
		return (NULL);
	if (p->type == PIPE)
		return (p);
	if (p->succ)
		return (first_pipe_after(p->succ));
	return (NULL);
}

t_phrase	*or_default(t_phrase *p, t_phrase *def)
{
	if (!p)
		return (def);
	return (p);
}
