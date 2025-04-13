/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:58:25 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/13 17:59:07 by jaehylee         ###   ########.fr       */
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
	if (tokens[k] && ft_strcmp((char *)tokens[k], "|") == 0)
		k++;
	*i = k;
	return (res);
}

char	*ft_get_env(t_list **dyn, const char *name)
{
	if (ft_strcmp((char *)name, "?") == 0)
		return (gc_itoa(dyn, g_signal));
	return (getenv(name));
}

ssize_t	parse_each(t_list **dyn, t_phrase **p, const char **tokens)
{
	if (ft_strcmp((char *)*tokens, "|") == 0)
		return (1);
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
