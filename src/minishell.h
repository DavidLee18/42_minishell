/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:03:52 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/16 02:22:24 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include "../ft_printf/src/ft_printf.h"
# ifndef MINISHELL
#  define MINISHELL "minishell"
# endif

extern int	g_exit_status;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

typedef enum e_cmd_type
{
	BUILTIN,
	NORMAL,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	REDIR_APND,
	PIPE
}	t_cmd_type;

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

typedef union u_debris
{
	int			fd;
	t_here_info	hinfo;
	char		**argv;
	t_pipe_rw	pipe_ends;
}	t_debris;

typedef struct s_phrase
{
	t_cmd_type		type;
	t_debris		deb;
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
_Bool		lex_preproc(char const *s, t_split_next *idxs, t_quote *p,
				_Bool *syll);
void		lex_pre_quote(char c, t_split_next *idxs, t_quote *p);
size_t		lex_split(t_list **dyn, char **split, char const *s);
_Bool		lex_split_range(t_list **dyn, char **split, char const *s,
				t_split_piece *sp);
size_t		lex_split_pos(const char *s, size_t i, t_split_piece *sp);
size_t		lex_split_pos2(const char *s, size_t i, t_split_piece *sp);
size_t		lex_split_final(t_list **dyn, char **split, char const *s,
				t_split_piece *sp);

t_phrase	*parse(t_list **dyn, const char **tokens);
ssize_t		parse_redir_in(t_list **dyn, t_phrase **p, const char **tokens);
ssize_t		parse_redir_out(t_list **dyn, t_phrase **p, const char **tokens);
ssize_t		parse_here_doc(t_list **dyn, t_phrase **p, const char **tokens);
ssize_t		parse_redir_apnd(t_list **dyn, t_phrase **p, const char **tokens);
ssize_t		parse_cmd_builtin(t_list **dyn, t_phrase **p, const char **tokens);
char		**parse_split_args(t_list **dyn, const char **tokens, ssize_t *i,
				const char *cmd);
ssize_t		parse_each(t_list **dyn, t_phrase **p, const char **tokens);
ssize_t		parse_pipe(t_list **dyn, t_phrase **p);
char		*unquote(t_list **dyn, const char *str);
char		*unquote_raw(t_list **dyn, const char *str);
_Bool		is_cmd(const char *str);
_Bool		is_builtin(const char *str);
char		*replace_env(t_list **dyn, const char *str);
t_phrase	*parse_lex(t_list **dyn, const char *str);

_Bool		phrase_spawn(t_list **dyn, t_phrase **p);
_Bool		is_space(char c);
char		**get_path(t_list **dyn);
char		*get_exec_path(t_list **dyn, const char *cmd);
void		print_phrase(t_phrase *p);
void		print_args(const char **args);
char		*ft_get_env(t_list **dyn, const char *name);
void		print_pipe(t_phrase *p);

char		*prompt(t_list **dyn);
_Bool		handle_signals(void);
void		set_signal(int s);
_Bool		unhandle_signals(void);
_Bool		ignore_signals(void);
void		process(t_list **dyn, t_phrase *p, char **envp, t_vec *pids);
int			here_doc(t_list **dyn, t_here_info *i, size_t n);
t_phrase	*phrase_head(t_phrase *p);
char		**get_cmd(t_phrase *p);
pid_t		exec_cmd(t_list **dyn, t_phrase *p, char **arg_env[2], t_pipe_rw *io);
void		process_exec_p(t_list **dyn, t_phrase *p, char **arg_env[2],
				t_pipe_rw *io);
size_t		count_here_docs(t_phrase *p);
void		close_pipes(t_phrase *p, t_pipe_rw *io, _Bool all);
t_pipe_rw	get_io(t_phrase **p);
void		close_wait(t_list **dyn, t_phrase *p, t_vec *pids);
char		*getln_until(t_list **dyn, char *limit, size_t n);
void		here_doc_prompt(size_t n);
void		close_pipes_pipes(t_phrase *p, t_pipe_rw *io, _Bool all);

int			exec_builtin(char *name, char **argv);
int			exec_echo(char **argv);
int			cd(char **argv);
int			pwd(char **argv);
int			exec_exit(char **argv);

#endif //MINISHELL_H
