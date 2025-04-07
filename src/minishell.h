/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:03:52 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/08 05:16:22 by jaehylee         ###   ########.fr       */
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

typedef union u_debris
{
	int		fd;
	char	*delim;
	char	**argv;
}	t_debris;

typedef struct s_phrase
{
	t_cmd_type		type;
	t_debris		deb;
	struct s_phrase	*pred;
	struct s_phrase	*succ;
}	t_phrase;

char		**lex(t_list **dyn, const char *str);
char		**lex_alloc(t_list **dyn, char const *s);
_Bool		lex_preproc(char const *s, t_split_next *idxs, t_quote *p,
				_Bool *syll);
void		lex_pre_paren(char c, t_split_next *idxs, t_quote *p);
_Bool		lex_split(t_list **dyn, char **split, char const *s);
_Bool		lex_split_range(t_list **dyn, char **split, char const *s,
				t_split_next *sp);
size_t		lex_len(const char *start, const char *prev, t_quote *p,
				_Bool *syll);
t_phrase	*parse(t_list **dyn, const char **tokens);
_Bool		is_space(char c);

#endif
