/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:03:52 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/23 23:23:07 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sysexits.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include "../../ft_printf/src/ft_printf.h"
# ifndef MINISHELL
#  define MINISHELL "minishell"
# endif
# ifndef S_HERE_DOC
#  define S_HERE_DOC 257
# endif

extern volatile sig_atomic_t	g_exit_status;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

typedef enum e_phrase_type
{
	BUILTIN,
	NORMAL,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	REDIR_APND,
	PIPE,
	AND_COMB,
	OR_COMB
}	t_phrase_type;

typedef struct s_here_info
{
	char	*delim;
	_Bool	raw;
}	t_here_info;

typedef struct s_pipe_rw
{
	int	write_end;
	int	read_end;
}	t_pipe_rw;

typedef struct s_phrase
{
	t_phrase_type	type;
	union u_debris
	{
		int			fd;
		t_here_info	hinfo;
		char		**argv;
		t_pipe_rw	pipe_ends;
		struct s_phrase_tree
		{
			struct s_phrase	*p1;
			struct s_phrase	*p2;
		}	tree;
	}	deb;
	struct s_phrase	*pred;
	struct s_phrase	*succ;
}	t_phrase;

typedef struct s_split_piece
{
	ssize_t	start;
	ssize_t	length;
}	t_split_piece;

char		**lex(t_list **dyn, const char *str);
char		**lex_alloc(t_list **dyn, char const *s);
_Bool		lex_preproc(const char *s, t_split_next *idxs, t_quote *p,
				_Bool *syll);
void		lex_pre_meta_syll(const char *s, t_split_next *idxs, _Bool *syll);
void		lex_pre_quote(char c, t_split_next *idxs, t_quote *p);
size_t		lex_split(t_list **dyn, char **split, char const *s);
_Bool		lex_split_range(t_list **dyn, char **split, char const *s,
				t_split_piece *sp);
size_t		lex_split_pos(const char *s, size_t i, t_split_piece *sp);
size_t		lex_split_pos2(const char *s, size_t i, t_split_piece *sp);
size_t		lex_split_final(t_list **dyn, char **split, char const *s,
				t_split_piece *sp);

t_phrase	*parse(t_list **dyn, const char **envp, const char **tokens);
ssize_t		parse_redir_in(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
ssize_t		parse_redir_out(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
ssize_t		parse_here_doc(t_list **dyn, t_phrase **p, const char **tokens);
ssize_t		parse_redir_apnd(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
ssize_t		parse_and(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
ssize_t		parse_or(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
ssize_t		parse_paren(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
ssize_t		parse_cmd_builtin(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
char		**parse_split_args(t_list **dyn, const char ***env_tok, ssize_t *i,
				const char *cmd);
ssize_t		parse_each(t_list **dyn, const char **envp,
				t_phrase **p, const char **tokens);
ssize_t		parse_pipe(t_list **dyn, t_phrase **p);
char		*unquote(t_list **dyn, const char **envp, const char *str);
char		*unquote_raw(t_list **dyn, const char *str);
_Bool		is_cmd(const char *str);
_Bool		is_builtin(const char *str);
char		*replace_env(t_list **dyn, const char **envp, const char *str);
t_phrase	*parse_lex(t_list **dyn, const char **envp, const char *str);
t_phrase	*cons_and(t_list **dyn, t_phrase *s1, t_phrase *s2);
t_phrase	*cons_or(t_list **dyn, t_phrase *s1, t_phrase *s2);

_Bool		phrase_spawn(t_list **dyn, t_phrase **p);
_Bool		is_space(char c);
char		**get_path(t_list **dyn, const char **envp);
char		*get_exec_path(t_list **dyn, const char **envp, const char *cmd);
_Bool		validate_cmd(t_list **dyn, const char **envp, char **cmd);
void		print_phrase(t_phrase *p, size_t nested);
void		print_args(const char **args);
char		*ft_get_env(t_list **dyn, const char **envp, const char *name);
void		print_pipe(t_phrase *p);
size_t		cmd_len(t_phrase *p);
size_t		pipe_cnt(t_phrase *p);
_Bool		contains_comb(t_phrase *p);
char		**subparen(t_list **dyn, const char **tokens);
char		**substrstr(t_list **dyn, const char **tokens, size_t start,
				size_t len);
void		print_comb(t_phrase *p, size_t nested);
void		print_cmd(t_phrase *p);
void		print_tabs(size_t n);

_Bool		handle_signals(void);
void		on_idle(int s);
_Bool		handle_signals_ch(void);
_Bool		ignore_signals(void);
void		on_here_doc(void);
void		off_here_doc(void);
_Bool		heredoc_signals(void);

char		*prompt(t_list **dyn);
_Bool		is_valid(t_phrase *ps, char *str);
void		process(t_list **dyn, t_phrase *p, char **envp, t_vec *pids);
void		switch_fds(t_list **dyn, t_phrase *p, char **envp, t_pipe_rw *io);
int			here_doc(t_list **dyn, const char **envp, t_phrase **p, size_t n);
t_phrase	*phrase_head(t_phrase *p);
t_phrase	*phrase_last(t_phrase *p);
t_phrase	*last_pipe(t_phrase *p);
t_phrase	*first_pipe_after(t_phrase *p);
t_phrase	*or_default(t_phrase *p, t_phrase *def);
char		**get_cmd(t_phrase *p);
pid_t		exec_cmd(t_list **dyn, t_phrase *p, char **arg_env[2],
				t_pipe_rw *io);
void		dup_io(t_list **dyn, t_phrase *p, t_pipe_rw *io);
size_t		count_here_docs(t_phrase *p);
void		close_pipes(t_phrase *p, t_pipe_rw *except);
void		close_fps_all(t_phrase *p);
void		close_fps_sub(t_phrase *parent, t_phrase *child_head,
				t_phrase *child_last);
void		close_io(t_pipe_rw *io);
t_pipe_rw	get_io(t_phrase **p);
void		close_wait(t_list **dyn, t_phrase *p, t_vec *pids, char ***envp);
char		*getln_until(t_list **dyn, char *limit, size_t n);
void		getln_loop(t_list **dyn, char *limit, size_t m[2], char **str);
char		*last_line(t_list **dyn, char *str);
void		here_doc_prompt(size_t n);
void		builtin_fd_swap(t_list **dyn, t_phrase *p, t_pipe_rw *io);
void		exec_builtin_message(t_list **dyn, int fe, pid_t pid, char ***envp);
_Bool		builtin_needs_swap(const char *str);

void		process_comb(t_list **dyn, t_phrase **p, char **envp, t_vec *pids);
pid_t		subshell(t_list **dyn, t_phrase *ps[2], char **envp, t_pipe_rw *io);
void		process_comb2(t_list **dyn, t_phrase **p, char **envp, t_vec *pids);
t_phrase	*push_phrase_front(t_list **dyn, t_phrase *p, t_phrase *p2);
t_phrase	*push_phrase_back(t_list **dyn, t_phrase *p, t_phrase *p2);
t_phrase	*next_branch(t_phrase *p);
void		rotate_up(t_vec *v);
void		rotate_down(t_vec *v);

int			exec_builtin(char **argv, char **envp);
int			exec_echo(char **argv);
int			cd(char **argv);
int			pwd(char **argv);
int			env(char **argv, char **envp);
int			exec_exit(char **argv);
int			export(char **argv);
int			unset(char **argv);
void		decree_cd(t_list **dyn, char **argv, const char **envp);
void		decree_export(t_list **dyn, char **argv, char ***envp);
void		decree_unset(t_list **dyn, char **argv, char ***envp);
void		decree_exit(t_list **dyn, char **argv, int exit_code);

char		*env_join(t_list **dyn, char **envp);
char		**env_copy(t_list **dyn, char **envp);
void		reset_env(t_list **dyn, char ***envp, char *argv);
void		export_print(t_list **dyn, char **envp);

#endif //MINISHELL_BONUS_H
