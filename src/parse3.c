/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:58:25 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/11 22:45:46 by jaehylee         ###   ########.fr       */
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
		var = ft_get_env(gc_substr(dyn, s, 0, i - s));
		if (var == NULL)
			return (NULL);
		temp = gc_strjoin(dyn, temp, var);
		s = i;
		i = ft_strchr(s, '$');
	}
	return (gc_strjoin(dyn, temp, s));
}

char	**parse_split_args(t_list **dyn, const char **tokens, size_t *i,
			const char *cmd)
{
	size_t	j;
	char	**res;

	j = *i;
	while (tokens[*i] && is_cmd(tokens[*i]))
		(*i)++;
	res = (char **)gc_calloc(dyn, *i - j + 2, sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = gc_strdup(dyn, cmd);
	if (j == *i)
		return (res);
	*i = j;
	while (tokens[*i] && is_cmd(tokens[*i]))
	{
		res[*i - j + 1] = unquote(dyn, tokens[*i]);
		(*i)++;
	}
	res[*i - j + 1] = NULL;
	if (tokens[*i] && ft_strcmp((char *)tokens[*i], "|") == 0)
		(*i)++;
	return (res);
}

char	*ft_get_env(const char *name)
{
	return (getenv(name));
}
