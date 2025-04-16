/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:30:22 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/16 11:41:17 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(const char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		ft_fprintf(STDOUT_FILENO, "%s ", args[i]);
		i++;
	}
	ft_fprintf(STDOUT_FILENO, "\n");
}

void	print_pipe(t_phrase *p)
{
	ft_fprintf(STDOUT_FILENO, "PIPE: read_end: %d, write_end: %d\n",
		p->deb.pipe_ends.read_end, p->deb.pipe_ends.write_end);
}

t_phrase	*phrase_head(t_phrase *p)
{
	if (!p || !p->pred)
		return (p);
	return (phrase_head(p->pred));
}

void	here_doc_prompt(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_fprintf(STDOUT_FILENO, ">");
		i++;
	}
	ft_fprintf(STDOUT_FILENO, " ");
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
