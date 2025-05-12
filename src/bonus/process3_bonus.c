/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:16:54 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/07 20:42:42 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*last_line(t_list **dyn, char *str)
{
	char	**ss;
	size_t	i;

	ss = gc_split(dyn, str, '\n');
	if (!ss || !*ss)
		return (NULL);
	i = 0;
	while (ss[i])
		i++;
	return (ss[i - 1]);
}

void	getln_loop(t_list **dyn, char *limit, size_t m[2], char **str)
{
	ssize_t	code;

	if (g_exit_status != S_HERE_DOC)
		return ;
	if (ft_strlen(*str) == 0)
		here_doc_prompt(m[0]);
	gc_realloc(dyn, (void **)str, m[1], m[1] + 2);
	code = read(STDIN_FILENO, *str + m[1], 1);
	if (code < 0)
	{
		*str = NULL;
		return ;
	}
	if (code == 0 && (ft_strlen(*str) == 0 || (*str)[m[1] - 1] == '\n'))
		return ;
	if (code > 0)
		(*str)[m[1] + code] = '\0';
	if ((*str)[m[1] + code - 1] == '\n'
		&& !ft_strcmp(last_line(dyn, *str), limit))
		return ;
	if (ft_strchr(*str + m[1], '\n'))
		here_doc_prompt(m[0]);
	getln_loop(dyn, limit, (size_t[]){m[0], m[1] + code}, str);
}

void	close_pipes(t_phrase *p, t_pipe_rw *except)
{
	if (!p)
		return ;
	if (p->type == AND_COMB || p->type == OR_COMB)
		(close_pipes(phrase_head(p->deb.tree.p1), except),
			close_pipes(phrase_head(p->deb.tree.p2), except));
	else if (p->type == PIPE)
	{
		if (except == NULL || (p->deb.pipe_ends.write_end != except->write_end
				&& p->deb.pipe_ends.write_end != except->read_end))
			close(p->deb.pipe_ends.write_end);
		if (except == NULL || (p->deb.pipe_ends.read_end != except->write_end
				&& p->deb.pipe_ends.read_end != except->read_end))
			close(p->deb.pipe_ends.read_end);
	}
	if (p->succ)
		close_pipes(p->succ, except);
}

void	close_io(t_pipe_rw *io)
{
	if (io->read_end > 2)
		close(io->read_end);
	if (io->write_end > 2)
		close(io->write_end);
}

_Bool	is_valid(t_phrase *ps, char *str)
{
	if (str && !*str)
		return (1);
	if (!ps && *str)
		return (ft_fprintf(STDERR_FILENO, "failed to parse: `%s`\n", str),
			free(str), close_fps_all(phrase_head(ps)), 0);
	if (ps->type == PIPE)
		return (ft_fprintf(STDERR_FILENO, "syntax error: `%s`\n"
				"starting by open pipe\n", str),
			free(str), close_fps_all(phrase_head(ps)), 0);
	while (ps && ps->succ)
	{
		if (ps->type == PIPE && ps->succ->type == PIPE)
			return (ft_fprintf(STDERR_FILENO, "syntax error: `%s`\n"
					"consecutive pipes\n", str),
				free(str), close_fps_all(phrase_head(ps)), 0);
		ps = ps->succ;
	}
	if (ps->type == PIPE && !ps->succ)
		return (ft_fprintf(STDERR_FILENO, "syntax error: `%s`\n"
				"finished with open pipe\n", str),
			free(str), close_fps_all(phrase_head(ps)), 0);
	return (1);
}
