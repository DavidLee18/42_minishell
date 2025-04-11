/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:56:42 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/11 12:10:29 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_phrase	*parse(t_list **dyn, const char **tokens)
{
	size_t		i;
	t_phrase	*p;

	i = 0;
	p = NULL;
	while (tokens[i] != NULL)
	{
		if (ft_strcmp((char *)tokens[i], "<") == 0
			&& !parse_redir_in(dyn, &p, tokens, &i))
			return (NULL);
		if (ft_strcmp((char *)tokens[i], ">") == 0
			&& !parse_redir_out(dyn, &p, tokens, &i))
			return (NULL);
		if (ft_strcmp((char *)tokens[i], "<<") == 0
			&& !parse_here_doc(dyn, &p, tokens, &i))
			return (NULL);
		if (ft_strcmp((char *)tokens[i], ">>") == 0
			&& !parse_redir_apnd(dyn, &p, tokens, &i))
			return (NULL);
		if (!parse_cmd_builtin(dyn, &p, tokens, &i))
			return (NULL);
	}
	return (p);
}

_Bool	parse_redir_in(t_list **dyn, t_phrase **p, const char **tokens,
			size_t *i)
{
	char	*infile;

	if (!phrase_spawn(dyn, p) || tokens[++(*i)] == NULL)
		return (0);
	(*p)->type = REDIR_IN;
	infile = unquote(dyn, tokens[(*i)++]);
	if (infile == NULL)
		return (0);
	if (ft_strchr(infile, '/') == NULL)
		infile = get_exec_path(dyn, infile);
	if (infile == NULL)
		return (0);
	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
		return (0);
	(*p)->deb.fd = open(infile, O_RDONLY);
	if ((*p)->deb.fd == -1)
		return (0);
	return (1);
}

_Bool	parse_redir_out(t_list **dyn, t_phrase **p, const char **tokens,
			size_t *i)
{
	char	*outfile;

	if (!phrase_spawn(dyn, p) || tokens[++(*i)] == NULL)
		return (0);
	(*p)->type = REDIR_OUT;
	outfile = unquote(dyn, tokens[(*i)++]);
	if (outfile == NULL)
		return (0);
	if (ft_strchr(outfile, '/') == NULL)
		outfile = get_exec_path(dyn, outfile);
	if (outfile == NULL)
		return (0);
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
		return (0);
	(*p)->deb.fd = open(outfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	if ((*p)->deb.fd == -1)
		return (0);
	return (1);
}

_Bool	parse_redir_apnd(t_list **dyn, t_phrase **p, const char **tokens,
			size_t *i)
{
	char	*apndfile;

	if (!phrase_spawn(dyn, p) || tokens[++(*i)] == NULL)
		return (0);
	(*p)->type = REDIR_APND;
	apndfile = unquote(dyn, tokens[(*i)++]);
	if (apndfile == NULL)
		return (0);
	if (ft_strchr(apndfile, '/') == NULL)
		apndfile = get_exec_path(dyn, apndfile);
	if (apndfile == NULL)
		return (0);
	if (access(apndfile, F_OK) == 0 && access(apndfile, W_OK) == -1)
		return (0);
	(*p)->deb.fd = open(apndfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	if ((*p)->deb.fd == -1)
		return (0);
	return (1);
}

_Bool	parse_here_doc(t_list **dyn, t_phrase **p, const char **tokens,
			size_t *i)
{
	char	*eof;

	if (!phrase_spawn(dyn, p) || tokens[++(*i)] == NULL)
		return (0);
	(*p)->type = HERE_DOC;
	if (tokens[*i][0] == '\"' || tokens[*i][0] == '\'')
		(*p)->deb.hinfo.raw = 1;
	else
		(*p)->deb.hinfo.raw = 0;
	eof = unquote_raw(dyn, tokens[(*i)++]);
	if (eof == NULL)
		return (0);
	(*p)->deb.hinfo.delim = eof;
	return (1);
}
