/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:54:10 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/07 11:56:27 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	print_pipe(t_phrase *p)
{
	ft_fprintf(STDOUT_FILENO, "PIPE: read_end: %d, write_end: %d\n",
		p->deb.pipe_ends.read_end, p->deb.pipe_ends.write_end);
}

size_t	cmd_len(t_phrase *p)
{
	char		**argv;
	size_t		len;

	if (!p)
		return (0);
	argv = get_cmd(p);
	if (!argv)
		return (0);
	len = 0;
	while (p && argv)
	{
		len++;
		while (p && p->type != PIPE)
			p = p->succ;
		if (p && p->type == PIPE)
			p = p->succ;
		argv = get_cmd(p);
	}
	return (len);
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

size_t	pipe_cnt(t_phrase *p)
{
	if (!p)
		return (0);
	if (p->type == PIPE)
		return (1 + pipe_cnt(p->succ));
	return (pipe_cnt(p->succ));
}
