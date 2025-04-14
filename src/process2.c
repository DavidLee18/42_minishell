/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:50:37 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/14 21:58:33 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_list **dyn, t_here_info *i, size_t n)
{
	int		p[2];
	char	*temp;

	if (pipe(p) == -1)
		return (perror(gc_strjoin(dyn, MINISHELL, ": pipe")), -1);
	temp = getln_until(dyn, i->delim, n);
	if (temp == NULL)
		return (close(p[0]), close(p[1]), -1);
	if (ft_strchr(temp, '$') == NULL || i->raw)
		ft_fprintf(p[1], temp);
	else
	{
		temp = replace_env(dyn, temp);
		if (!temp)
			return (close(p[1]), p[0]);
		ft_fprintf(p[1], temp);
	}
	return (close(p[1]), p[0]);
}

size_t	count_here_docs(t_phrase *p)
{
	if (p && p->type == HERE_DOC)
		return (1 + count_here_docs(p->succ));
	if (!p || p->type == PIPE)
		return (0);
	return (count_here_docs(p->succ));
}

void	close_pipes(t_phrase *p, t_pipe_rw *except, _Bool all)
{
	if (!p)
		return ;
	if (p->pred)
		close_pipes(p->pred, except, all);
	else if (p->type == REDIR_IN || p->type == REDIR_OUT
		|| p->type == REDIR_APND)
	{
		if (!except || all)
			close(p->deb.fd);
		else if (p->deb.fd > 2 && p->deb.fd != except->read_end
			&& p->deb.fd != except->write_end)
			close(p->deb.fd);
	}
	else if (p->type == PIPE)
	{
		if (!except || all)
			(close(p->deb.pipe_ends.read_end),
				close(p->deb.pipe_ends.write_end));
		else if ((p->deb.pipe_ends.read_end > 2
				&& p->deb.pipe_ends.read_end != except->read_end
				&& p->deb.pipe_ends.read_end != except->write_end)
			&& (p->deb.pipe_ends.write_end > 2 && p->deb.pipe_ends.write_end
				!= except->read_end && p->deb.pipe_ends.write_end
				!= except->write_end))
			(close(p->deb.pipe_ends.read_end),
				close(p->deb.pipe_ends.write_end));
	}
}

void	close_wait(t_phrase *p)
{
	int	stat;

	stat = 0;
	close_pipes(p, NULL, 1);
	waitpid(-1, &stat, 0);
	if (WIFEXITED(stat))
		g_exit_status = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
	{
		g_exit_status = WTERMSIG(stat) + 128;
		if (WTERMSIG(stat) == SIGQUIT)
			ft_fprintf(STDERR_FILENO, "Quit (core dumped)\n");
	}
}

char	*getln_until(t_list **dyn, char *limit, size_t n)
{
	char	*str;
	char	*temp;

	str = "";
	here_doc_prompt(n);
	temp = gc_getline(dyn, STDIN_FILENO);
	while (temp != NULL && ft_strcmp(gc_strtrim(dyn, temp, "\n"), limit) != 0)
	{
		str = gc_strjoin(dyn, str, temp);
		here_doc_prompt(n);
		temp = gc_getline(dyn, STDIN_FILENO);
	}
	if (temp == NULL)
		return (ft_fprintf(STDERR_FILENO, "%s: expected \'%s\', got EOF\n",
				MINISHELL, limit), str);
	if (ft_strcmp(gc_strtrim(dyn, temp, "\n"), limit) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: expected \'%s\', got EOF\n", MINISHELL,
			limit);
		return (gc_strjoin(dyn, str, temp));
	}
	return (str);
}
