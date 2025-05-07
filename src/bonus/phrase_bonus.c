/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:50:28 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/07 11:52:11 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

_Bool	phrase_spawn(t_list **dyn, t_phrase **p)
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
		*p = (*p)->succ;
	}
	return (1);
}

void	print_phrase(t_phrase *p, size_t nested)
{
	if (p == NULL)
		return ;
	print_tabs(nested);
	if (p->type == REDIR_IN)
		ft_fprintf(STDOUT_FILENO, "REDIR_IN: %d\n", p->deb.fd);
	else if (p->type == REDIR_OUT)
		ft_fprintf(STDOUT_FILENO, "REDIR_OUT: %d\n", p->deb.fd);
	else if (p->type == REDIR_APND)
		ft_fprintf(STDOUT_FILENO, "REDIR_APND: %d\n", p->deb.fd);
	else if (p->type == HERE_DOC)
	{
		ft_fprintf(STDOUT_FILENO, "HERE_DOC: %s", p->deb.hinfo.delim);
		if (p->deb.hinfo.raw)
			ft_fprintf(STDOUT_FILENO, "(RAW)");
		ft_fprintf(STDOUT_FILENO, "\n");
	}
	else if (p->type == PIPE)
		print_pipe(p);
	else if (p->type == BUILTIN || p->type == NORMAL)
		print_cmd(p);
	else
		print_comb(p, nested);
	if (p->succ != NULL)
		print_phrase(p->succ, nested);
}

t_phrase	*phrase_head(t_phrase *p)
{
	if (!p || !p->pred)
		return (p);
	return (phrase_head(p->pred));
}

t_phrase	*cons_and(t_list **dyn, t_phrase *s1, t_phrase *s2)
{
	t_phrase	*p;

	if (!s1 || !s2)
		return (NULL);
	p = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
	if (!p)
		return (NULL);
	p->type = AND_COMB;
	p->deb.tree.p1 = s1;
	p->deb.tree.p2 = s2;
	p->pred = s1->pred;
	s1->pred = NULL;
	return (p);
}

t_phrase	*cons_or(t_list **dyn, t_phrase *s1, t_phrase *s2)
{
	t_phrase	*p;

	if (!s1 || !s2)
		return (NULL);
	p = (t_phrase *)gc_calloc(dyn, 1, sizeof(t_phrase));
	if (!p)
		return (NULL);
	p->type = OR_COMB;
	p->deb.tree.p1 = s1;
	p->deb.tree.p2 = s2;
	return (p);
}
