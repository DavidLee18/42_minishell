/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:14:29 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/23 04:04:13 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	here_doc(t_list **dyn, const char **envp, t_phrase **p, size_t n)
{
	int		pfd[2];
	char	*temp;

	if (pipe(pfd) == -1)
		return (perror(gc_strjoin(dyn, MINISHELL, ": pipe")), -1);
	on_here_doc();
	temp = getln_until(dyn, (*p)->deb.hinfo.delim, n);
	if (temp == NULL || n > 1)
	{
		g_exit_status = 1;
		return (off_here_doc(), close(pfd[0]), close(pfd[1]), -1);
	}
	(*p)->type = REDIR_IN;
	(*p)->deb.fd = pfd[0];
	if (ft_strchr(temp, '$') != NULL && !(*p)->deb.hinfo.raw)
	{
		temp = replace_env(dyn, envp, temp);
		if (!temp)
		{
			g_exit_status = 1;
			return (off_here_doc(), close(pfd[1]), pfd[0]);
		}
	}
	g_exit_status = 0;
	return (ft_fprintf(pfd[1], temp), off_here_doc(), close(pfd[1]), pfd[0]);
}

size_t	count_here_docs(t_phrase *p)
{
	if (p && p->type == HERE_DOC)
		return (1 + count_here_docs(p->succ));
	if (!p || p->type == PIPE)
		return (0);
	if (p->type == AND_COMB || p->type == OR_COMB)
	{
		if (p->deb.tree.p1)
			return (count_here_docs(p->deb.tree.p1));
		return (count_here_docs(p->deb.tree.p2));
	}
	return (count_here_docs(p->succ));
}

void	close_fps_all(t_phrase *p)
{
	if (!p)
		return ;
	else if (p->type == REDIR_IN || p->type == REDIR_OUT
		|| p->type == REDIR_APND)
		close(p->deb.fd);
	else if (p->type == PIPE)
		(close(p->deb.pipe_ends.write_end),
			close(p->deb.pipe_ends.read_end));
	else if (p->type == AND_COMB || p->type == OR_COMB)
		(close_fps_all(p->deb.tree.p1), close_fps_all(p->deb.tree.p2));
	if (p->succ)
		close_fps_all(p->succ);
}

void	close_wait(t_list **dyn, t_phrase *p, t_vec *pids, char ***envp)
{
	int	stat;
	int	*id;

	stat = 0;
	close_fps_all(p);
	id = pop_back(dyn, pids);
	if (id && g_exit_status < -1)
		return (exec_builtin_message(dyn, -g_exit_status, *id, envp));
	while (id)
	{
		waitpid(*id, &stat, 0);
		if (WIFEXITED(stat))
			g_exit_status = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
		{
			g_exit_status = WTERMSIG(stat) + 128;
			if (WTERMSIG(stat) == SIGQUIT)
				ft_fprintf(STDOUT_FILENO, "Quit (core dumped)");
			ft_fprintf(STDOUT_FILENO, "\n");
		}
		id = pop_back(dyn, pids);
	}
	handle_signals();
}

char	*getln_until(t_list **dyn, char *limit, size_t n)
{
	char	*str;

	str = gc_strdup(dyn, "");
	getln_loop(dyn, limit, (size_t[]){n, 0}, &str);
	if (g_exit_status != S_HERE_DOC)
		return (str);
	if (!str || ft_strlen(str) == 0
		|| (last_line(dyn, str) && ft_strcmp(last_line(dyn, str), limit) != 0))
		return (ft_fprintf(STDERR_FILENO, "\n%s: expected \'%s\', got EOF\n",
				MINISHELL, limit), str);
	if (str && *str && str[ft_strlen(str) - 1] == '\n' && last_line(dyn, str)
		&& ft_strcmp(last_line(dyn, str), limit) == 0
		&& ft_strnstr(str, limit, ft_strlen(str)))
	{
		str = gc_strtrim(dyn, str, "\n");
		ft_strrchr(str, '\n')[1] = 0;
		return (str);
	}
	return (str);
}
