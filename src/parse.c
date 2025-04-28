/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:56:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/29 00:22:59 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_phrase	*parse(t_list **dyn, const char **envp, const char **tokens)
{
	size_t		i;
	ssize_t		j;
	t_phrase	*p;

	i = 0;
	j = 0;
	p = NULL;
	while (tokens[i] != NULL)
	{
		j = parse_each(dyn, envp, &p, tokens + i);
		if (j < 0)
			return (NULL);
		i += j;
	}
	return (p);
}

ssize_t	parse_redir_in(t_list **dyn, const char **envp,
	t_phrase **p, const char **tokens)
{
	char	*infile;

	if (!phrase_spawn(dyn, p) || tokens[1] == NULL)
		return (-1);
	(*p)->type = REDIR_IN;
	infile = unquote(dyn, envp, tokens[1]);
	if (infile == NULL || !is_cmd(infile))
		return (-1);
	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
		return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
					infile)), -1);
	(*p)->deb.fd = open(infile, O_RDONLY);
	if ((*p)->deb.fd == -1)
		return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
					infile)), -1);
	return (2);
}

ssize_t	parse_redir_out(t_list **dyn, const char **envp,
	t_phrase **p, const char **tokens)
{
	char	*outfile;

	if (!phrase_spawn(dyn, p) || tokens[1] == NULL)
		return (-1);
	(*p)->type = REDIR_OUT;
	outfile = unquote(dyn, envp, tokens[1]);
	if (outfile == NULL || !is_cmd(outfile))
		return (-1);
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
		return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
					outfile)), -1);
	(*p)->deb.fd = open(outfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	if ((*p)->deb.fd == -1)
		return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
					outfile)), -1);
	return (2);
}

ssize_t	parse_redir_apnd(t_list **dyn, const char **envp,
	t_phrase **p, const char **tokens)
{
	char	*apndfile;

	if (!phrase_spawn(dyn, p) || tokens[1] == NULL)
		return (-1);
	(*p)->type = REDIR_APND;
	apndfile = unquote(dyn, envp, tokens[1]);
	if (apndfile == NULL || !is_cmd(apndfile))
		return (-1);
	if (access(apndfile, F_OK) == 0 && access(apndfile, W_OK) == -1)
		return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
					apndfile)), -1);
	(*p)->deb.fd = open(apndfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	if ((*p)->deb.fd == -1)
		return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
					apndfile)), -1);
	return (2);
}

ssize_t	parse_here_doc(t_list **dyn, t_phrase **p, const char **tokens)
{
	char	*eof;

	if (!phrase_spawn(dyn, p) || tokens[1] == NULL || !is_cmd(tokens[1]))
		return (-1);
	(*p)->type = HERE_DOC;
	if (tokens[1][0] == '\"' || tokens[1][0] == '\'')
		(*p)->deb.hinfo.raw = 1;
	else
		(*p)->deb.hinfo.raw = 0;
	eof = unquote_raw(dyn, tokens[1]);
	if (eof == NULL)
		return (-1);
	(*p)->deb.hinfo.delim = eof;
	return (2);
}
