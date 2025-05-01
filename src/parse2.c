/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:55:38 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/29 02:09:40 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	parse_cmd_builtin(t_list **dyn, const char **envp,
	t_phrase **p, const char **tokens)
{
	char	*cmd;
	ssize_t	i;

	if (!phrase_spawn(dyn, p) || *tokens == NULL)
		return (-1);
	cmd = unquote(dyn, envp, *tokens);
	if (!cmd)
		return (-1);
	if (is_builtin(cmd))
		(*p)->type = BUILTIN;
	else
	{
		(*p)->type = NORMAL;
		if (!validate_cmd(dyn, envp, &cmd))
			return (-1);
	}
	i = 0;
	(*p)->deb.argv = parse_split_args(dyn, (const char **[]){envp, tokens},
			&i, cmd);
	if ((*p)->deb.argv == NULL)
		return (-1);
	return (i);
}

char	*unquote_raw(t_list **dyn, const char *str)
{
	if (*str == '\'' || *str == '\"')
		return (gc_substr(dyn, str, 1, ft_strlen(str) - 2));
	return ((char *)str);
}

char	**get_path(t_list **dyn, const char **envp)
{
	char	**path;
	char	*raw_path;

	raw_path = ft_get_env(dyn, envp, "PATH");
	if (raw_path == NULL)
		return (NULL);
	path = gc_split(dyn, raw_path, ':');
	if (path == NULL || path[0] == NULL)
		return (NULL);
	return (path);
}

char	*get_exec_path(t_list **dyn, const char **envp, const char *cmd)
{
	size_t	i;
	char	*temp_path;
	char	**path;

	i = 0;
	path = get_path(dyn, envp);
	if (path == NULL)
		return (NULL);
	while (path && path[i])
	{
		temp_path = gc_strjoin(dyn, path[i], "/");
		if (temp_path == NULL)
			return (NULL);
		temp_path = gc_strjoin(dyn, temp_path, cmd);
		if (temp_path != NULL && access(temp_path, X_OK) == 0)
			return (temp_path);
		i++;
	}
	return (perror(gc_strjoin(dyn, gc_strjoin(dyn, MINISHELL, ": "),
				cmd)), NULL);
}

char	*unquote(t_list **dyn, const char **envp, const char *str)
{
	char	*raw;
	char	*res;

	if (*str == '\'')
		return (gc_substr(dyn, str, 1, ft_strlen(str) - 2));
	if (*str == '\"')
		raw = gc_substr(dyn, str, 1, ft_strlen(str) - 2);
	else
		raw = (char *)str;
	if (ft_strchr(raw, '$') == NULL)
		return (raw);
	res = replace_env(dyn, envp, raw);
	if (!res)
		return (gc_strdup(dyn, ""));
	return (res);
}
