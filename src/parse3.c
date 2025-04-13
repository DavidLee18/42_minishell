/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:58:25 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/14 03:47:50 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (temp == NULL)
			return (NULL);
		s = ++i;
		while ((*i >= 'A' && *i <= 'Z') || *i == '_' || *i == '?')
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

ssize_t	parse_pipe(t_list **dyn, t_phrase **p)
{
	int	rw[2];

	if (!phrase_spawn(dyn, p))
		return (-1);
	(*p)->type = PIPE;
	if (pipe(rw) == -1)
		return (perror(gc_strjoin(dyn, MINISHELL, ": pipe")), -1);
	(*p)->deb.pipe_ends = (t_pipe_rw){.read_end = rw[0], .write_end = rw[1]};
	return (1);
}
