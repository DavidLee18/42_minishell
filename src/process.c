/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:23:13 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/15 03:05:23 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process(t_list **dyn, t_phrase *p, char **envp)
{
	t_pipe_rw	io;
	char		**argv;

	io = get_io(&p);
	argv = get_cmd(p);
	if (argv == NULL)
	{
		ft_fprintf(STDERR_FILENO, "%s: syntax error: invalid number of"
			" commands\n", MINISHELL);
		return ;
	}
	while (p && p->type != PIPE)
	{
		if (p->type == REDIR_IN)
			io.read_end = p->deb.fd;
		else if (p->type == REDIR_OUT || p->type == REDIR_APND)
			io.write_end = p->deb.fd;
		else if (p->type == HERE_DOC)
			io.read_end = here_doc(dyn, &p->deb.hinfo, count_here_docs(p));
		p = p->succ;
	}
	if (!p)
		exec_cmd(dyn, p, (char **[]){argv, envp}, &io);
	else
		process_exec_p(dyn, p, (char **[]){argv, envp}, &io);
}

void	exec_cmd(t_list **dyn, t_phrase *p, char **arg_env[2], t_pipe_rw *io)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		perror(gc_strjoin(dyn, MINISHELL, ": fork"));
	else if (id == 0)
	{
		if (io->read_end == -1 || (io->read_end != STDIN_FILENO
				&& dup2(io->read_end, STDIN_FILENO) == -1)
			|| io->write_end == -1 || (io->write_end != STDOUT_FILENO
				&& dup2(io->write_end, STDOUT_FILENO) == -1))
			(gc_free_all(*dyn), close_pipes(phrase_head(p), io, 1),
				exit(EXIT_FAILURE));
		close_pipes(phrase_head(p), io, 0);
		if (is_builtin(arg_env[0][0]))
		{
			g_exit_status = exec_builtin(arg_env[0][0], arg_env[0]);
			gc_free_all(*dyn);
			exit(g_exit_status);
		}
		execve(arg_env[0][0], arg_env[0], arg_env[1]);
		gc_free_all(*dyn);
		exit(EXIT_FAILURE);
	}
	g_exit_status = -id;
}

void	process_exec_p(t_list **dyn, t_phrase *p, char **arg_env[2],
			t_pipe_rw *io)
{
	if (p->type != PIPE)
		return ;
	io->write_end = p->deb.pipe_ends.write_end;
	exec_cmd(dyn, p, arg_env, io);
	process(dyn, p, arg_env[1]);
}

char	**get_cmd(t_phrase *p)
{
	char	**argv;

	argv = NULL;
	while (1)
	{
		while (p && p->type != NORMAL && p->type != BUILTIN && p->type != PIPE)
			p = p->succ;
		if (!p || p->type == PIPE)
			return (argv);
		else if (p->type != NORMAL && p->type != BUILTIN)
			p = p->succ;
		else if (argv == NULL)
		{
			argv = p->deb.argv;
			p = p->succ;
		}
		else
			return (NULL);
	}
}

t_pipe_rw	get_io(t_phrase **p)
{
	t_pipe_rw	io;

	io = (t_pipe_rw){.read_end = STDIN_FILENO, .write_end = STDOUT_FILENO};
	if (!*p)
		return (io);
	if ((*p)->type != PIPE)
		return (io);
	io.read_end = (*p)->deb.pipe_ends.read_end;
	*p = (*p)->succ;
	return (io);
}
