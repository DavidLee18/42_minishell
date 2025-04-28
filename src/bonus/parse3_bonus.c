/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:22:51 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/29 03:04:51 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*replace_env(t_list **dyn, const char *str)
{
	char	*i;
	char	*s;
	char	*temp;
	char	*var;

	temp = "";
	s = (char *)str;
	i = ft_strchr(s, '$');
	while (i != NULL)
	{
		temp = gc_strjoin(dyn, temp, gc_substr(dyn, s, 0, i - s));
		s = ++i;
		if (ft_isalpha(*i) || *i == '_' || *i == '?')
			i++;
		while (ft_isalnum(*i) || *i == '_' || *i == '?')
			i++;
		var = ft_get_env(dyn, gc_substr(dyn, s, 0, i - s));
		if (var == NULL)
			return (NULL);
		temp = gc_strjoin(dyn, temp, var);
		s = i;
		i = ft_strchr(s, '$');
	}
	return (gc_strjoin(dyn, temp, s));
}

char	**parse_split_args(t_list **dyn, const char **tokens, ssize_t *i,
			const char *cmd)
{
	size_t	k;
	char	**res;

	k = *i + 1;
	(*i)++;
	while (tokens[k] && is_cmd(tokens[k]))
		k++;
	res = (char **)gc_calloc(dyn, k - *i + 2, sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = gc_strdup(dyn, cmd);
	if ((size_t)(*i) == k)
		return (res);
	k = *i;
	while (tokens[k] && is_cmd(tokens[k]))
	{
		res[k - *i + 1] = unquote(dyn, tokens[k]);
		k++;
	}
	res[k - *i + 1] = NULL;
	*i = k;
	return (res);
}

char	*ft_get_env(t_list **dyn, const char *name)
{
	if (ft_strcmp((char *)name, "?") == 0)
		return (gc_itoa(dyn, g_exit_status));
	return (getenv(name));
}

ssize_t	parse_each(t_list **dyn, t_phrase **p, const char **tokens)
{
	if (ft_strcmp((char *)*tokens, "&&") == 0)
		return (parse_and(dyn, p, tokens));
	if (ft_strcmp((char *)*tokens, "||") == 0)
		return (parse_or(dyn, p, tokens));
	if (ft_strcmp((char *)*tokens, "(") == 0
		|| ft_strcmp((char *)*tokens, ")") == 0)
		return (parse_paren(dyn, p, tokens));
	if (ft_strcmp((char *)*tokens, "|") == 0)
		return (parse_pipe(dyn, p));
	if (ft_strcmp((char *)*tokens, "<") == 0)
		return (parse_redir_in(dyn, p, tokens));
	if (ft_strcmp((char *)*tokens, ">") == 0)
		return (parse_redir_out(dyn, p, tokens));
	if (ft_strcmp((char *)*tokens, ">>") == 0)
		return (parse_redir_apnd(dyn, p, tokens));
	if (ft_strcmp((char *)*tokens, "<<") == 0)
		return (parse_here_doc(dyn, p, tokens));
	return (parse_cmd_builtin(dyn, p, tokens));
}

ssize_t	parse_pipe(t_list **dyn, t_phrase **ps)
{
	int			rw[2];
	t_phrase	**p;

	p = get_curr_phrase(dyn, ps);
	if (!p)
		return (-1);
	(*p)->type = PIPE;
	if (pipe(rw) == -1)
		return (perror(gc_strjoin(dyn, MINISHELL, ": pipe")), -1);
	(*p)->deb.pipe_ends = (t_pipe_rw){.read_end = rw[0], .write_end = rw[1]};
	return (1);
}
