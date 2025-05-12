/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 06:00:27 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/09 16:34:01 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	rotate_up(t_vec *v)
{
	int		temp;
	size_t	i;

	if (v->len == 0)
		return ;
	temp = v->ptr[v->len - 1];
	i = 0;
	while (i < v->len - 1)
	{
		v->ptr[i + 1] = v->ptr[i];
		i++;
	}
	v->ptr[0] = temp;
}

void	rotate_down(t_vec *v)
{
	int		temp;
	size_t	i;

	if (v->len == 0)
		return ;
	temp = v->ptr[0];
	i = v->len - 1;
	while (i > 0)
	{
		v->ptr[i - 1] = v->ptr[i];
		i--;
	}
	v->ptr[v->len - 1] = temp;
}
