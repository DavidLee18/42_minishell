/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc4_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 01:35:13 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/30 11:56:01 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	**substrstr(t_list **dyn, const char **tokens, size_t start, size_t len)
{
	char	**ss;
	size_t	i;

	if (len == 0)
		return (NULL);
	ss = (char **)gc_calloc(dyn, len + 1, sizeof(char *));
	if (!ss)
		return (NULL);
	i = start;
	while (i < start + len)
	{
		ss[i - start] = (char *)tokens[i];
		i++;
	}
	ss[i - start] = NULL;
	return (ss);
}

void	print_comb(t_phrase *p, size_t nested)
{
	if (p->type == AND_COMB)
		ft_fprintf(STDOUT_FILENO, "AND_COMB: \n");
	else if (p->type == OR_COMB)
		ft_fprintf(STDOUT_FILENO, "OR_COMB: \n");
	print_tabs(nested);
	ft_fprintf(STDOUT_FILENO, "p1: \n");
	print_phrase(p->deb.tree.p1, nested + 1);
	print_tabs(nested);
	ft_fprintf(STDOUT_FILENO, "p2: \n");
	print_phrase(p->deb.tree.p2, nested + 1);
}

void	print_cmd(t_phrase *p)
{
	if (p->type == BUILTIN)
		ft_fprintf(STDOUT_FILENO, "BUILTIN: ");
	else if (p->type == NORMAL)
		ft_fprintf(STDOUT_FILENO, "NORMAL: ");
	if (p->type == BUILTIN || p->type == NORMAL)
		print_args((const char **)p->deb.argv);
}

void	print_tabs(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_fprintf(STDOUT_FILENO, "\t");
		i++;
	}
}
