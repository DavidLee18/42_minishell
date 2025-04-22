/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 02:22:50 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/22 17:53:12 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	ignore_signals(void)
{
	struct sigaction	act;
	sigset_t			masks;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&masks);
	sigaddset(&masks, SIGINT);
	sigaddset(&masks, SIGQUIT);
	act.sa_mask = masks;
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (0);
	return (1);
}

void	builtin_fd_swap(t_list **dyn, t_phrase *p, t_pipe_rw *io)
{
	int			fp[2];
	t_phrase	*p_;
	char		**argv;

	p_ = phrase_head(p);
	argv = get_cmd(p_);
	if (cmd_len(p_) != 1 || !argv || !is_builtin(argv[0])
		|| !builtin_needs_swap(argv[0]))
		return ;
	if (pipe(fp) == -1)
	{
		perror(gc_strjoin(dyn, MINISHELL, ": pipe"));
		return ;
	}
	io->write_end = fp[1];
	g_exit_status = -fp[0];
}

void	exec_builtin_message(t_list **dyn, int fd, pid_t pid)
{
	int		stat;
	char	*str;

	stat = 0;
	waitpid(pid, &stat, 0);
	str = NULL;
	str = gc_getline(dyn, fd);
	if (str && ft_strncmp(str, "cd", 2))
		decree_cd(dyn, gc_split(dyn, str, ' '));
	else if (str && ft_strncmp(str, "export", 6))
		decree_export(dyn, gc_split(dyn, str, ' '));
	else if (str && ft_strncmp(str, "unset", 5))
		decree_unset(dyn, gc_split(dyn, str, ' '));
	else if (str && ft_strncmp(str, "exit", 4))
		decree_exit(dyn, gc_split(dyn, str, ' '));
	if (WIFEXITED(stat))
		g_exit_status = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
	{
		g_exit_status = 1;
		ft_fprintf(STDOUT_FILENO, "\n");
	}
}
