/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:35:29 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 22:35:50 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	int			temp_exit_status;

	temp_exit_status = g_exit_status;
	p_ = phrase_head(p);
	argv = get_cmd(p_);
	if (cmd_len(p_) != 1 || !argv || !is_builtin(argv[0])
		|| !builtin_needs_swap(argv[0]))
	{
		g_exit_status = -1;
		return ;
	}
	if (pipe(fp) == -1)
		return (perror(gc_strjoin(dyn, MINISHELL, ": pipe")));
	io->write_end = fp[1];
	if (pipe_cnt(p) > 0)
		close(fp[0]);
	g_exit_status = -(fp[0] * (pipe_cnt(p) == 0) << 8 | temp_exit_status);
}

void	exec_builtin_message(t_list **dyn, int fe, pid_t pid, char ***envp)
{
	int		stat;
	char	*str;

	stat = 0;
	waitpid(pid, &stat, 0);
	str = NULL;
	if ((fe & 0xff00) >> 8 == 0)
		return ;
	str = gc_getline(dyn, (fe & 0xff00) >> 8);
	if (str && ft_strncmp(str, "cd", 2) == 0)
		decree_cd(dyn, gc_split(dyn, str, ' '), (const char **)*envp);
	else if (str && ft_strncmp(str, "export", 6) == 0)
		decree_export(dyn, gc_split(dyn, str, ' '), envp);
	else if (str && ft_strncmp(str, "unset", 5) == 0)
		decree_unset(dyn, gc_split(dyn, str, ' '), envp);
	else if (str && ft_strncmp(str, "exit", 4) == 0)
		decree_exit(dyn, gc_split(dyn, str, ' '), fe & 0xff);
	if (WIFEXITED(stat))
		g_exit_status = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
	{
		g_exit_status = 1;
		ft_fprintf(STDOUT_FILENO, "\n");
	}
}

void	on_here_doc(void)
{
	struct termios	term;

	g_exit_status = S_HERE_DOC;
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	heredoc_signals();
}

void	off_here_doc(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	handle_signals();
}
