/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:03:34 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/13 19:45:02 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

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

_Bool	is_cmd(const char *str)
{
	return (ft_strcmp((char *)str, "<") && ft_strcmp((char *)str, ">")
		&& ft_strcmp((char *)str, "<<") && ft_strcmp((char *)str, ">>")
		&& ft_strcmp((char *)str, "|"));
}

_Bool	is_builtin(const char *str)
{
	return (ft_strcmp((char *)str, "echo") == 0
		|| ft_strcmp((char *)str, "cd") == 0
		|| ft_strcmp((char *)str, "pwd") == 0
		|| ft_strcmp((char *)str, "export") == 0
		|| ft_strcmp((char *)str, "unset") == 0
		|| ft_strcmp((char *)str, "env") == 0
		|| ft_strcmp((char *)str, "exit") == 0);
}

void	print_phrase(t_phrase *p)
{
	if (p == NULL)
		return ;
	if (p->pred != NULL)
		print_phrase(p->pred);
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
	else if (p->type == BUILTIN)
		ft_fprintf(STDOUT_FILENO, "BUILTIN: ");
	else
		ft_fprintf(STDOUT_FILENO, "NORMAL: ");
	if (p->type == BUILTIN || p->type == NORMAL)
		print_args((const char **)p->deb.argv);
}
