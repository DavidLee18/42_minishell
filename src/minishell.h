/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:03:52 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/13 17:53:39 by jaehylee         ###   ########.fr       */
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

extern unsigned char	g_signal;

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
	REDIR_APND
}	t_cmd_type;

typedef struct s_here_info
{
	char	*delim;
	_Bool	raw;
}	t_here_info;

typedef union u_debris
{
	int			fd;
	t_here_info	hinfo;
	char		**argv;
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

_Bool		phrase_spawn(t_list **dyn, t_phrase **p);
_Bool		is_space(char c);
char		*unquote(t_list **dyn, const char *str);
char		*unquote_raw(t_list **dyn, const char *str);
char		**get_path(t_list **dyn);
char		*get_exec_path(t_list **dyn, const char *cmd);
_Bool		is_cmd(const char *str);
_Bool		is_builtin(const char *str);
char		*replace_env(t_list **dyn, const char *str);
void		print_phrase(t_phrase *p);
void		print_args(const char **args);
char		*ft_get_env(t_list **dyn, const char *name);

char		*prompt(t_list **dyn);
_Bool		handle_signals(void);
void		set_signal(int s);
t_phrase	*parse_lex(t_list **dyn, const char *str);

#endif //MINISHELL_H
