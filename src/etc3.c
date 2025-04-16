/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:25:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/16 13:00:13 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	builtin_needs_swap(const char *str)
{
	return (ft_strcmp((char *)str, "cd") == 0
		|| ft_strcmp((char *)str, "export") == 0
		|| ft_strcmp((char *)str, "unset") == 0
		|| ft_strcmp((char *)str, "exit") == 0);
}
