/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:22:51 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 21:52:38 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*replace_env(t_list **dyn, const char **envp, const char *str)
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
		var = ft_get_env(dyn, envp, gc_substr(dyn, s, 0, i - s));
		if (var == NULL)
			return (NULL);
		temp = gc_strjoin(dyn, temp, var);
		s = i;
		i = ft_strchr(s, '$');
	}
	return (gc_strjoin(dyn, temp, s));
}

char	**parse_split_args(t_list **dyn, const char ***env_tok, ssize_t *i,
			const char *cmd)
{
	size_t	k;
	char	**res;

	k = *i + 1;
	(*i)++;
	while (env_tok[1][k] && is_cmd(env_tok[1][k]))
		k++;
	res = (char **)gc_calloc(dyn, k - *i + 2, sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = gc_strdup(dyn, cmd);
	if ((size_t)(*i) == k)
		return (res);
	k = *i;
	while (env_tok[1][k] && is_cmd(env_tok[1][k]))
	{
		res[k - *i + 1] = unquote(dyn, env_tok[0], env_tok[1][k]);
		k++;
	}
	res[k - *i + 1] = NULL;
	*i = k;
	return (res);
}

char	*ft_get_env(t_list **dyn, const char **envp, const char *name)
{
	size_t	i;
	char	**ss;

	if (ft_strcmp((char *)name, "?") == 0)
		return (gc_itoa(dyn, g_exit_status));
	i = 0;
	ss = NULL;
	while (envp[i])
	{
		ss = gc_split(dyn, envp[i], '=');
		if (!ss)
			return (NULL);
		if (ft_strcmp(ss[0], (char *)name) == 0)
			return (ss[1]);
		i++;
	}
	return (NULL);
}

ssize_t	parse_each(t_list **dyn, const char **envp,
	t_phrase **p, const char **tokens)
{
	if (ft_strcmp((char *)*tokens, "&&") == 0)
		return (parse_and(dyn, envp, p, tokens));
	if (ft_strcmp((char *)*tokens, "||") == 0)
		return (parse_or(dyn, envp, p, tokens));
	if (ft_strcmp((char *)*tokens, "(") == 0
		|| ft_strcmp((char *)*tokens, ")") == 0)
		return (parse_paren(dyn, envp, p, tokens));
	if (ft_strcmp((char *)*tokens, "|") == 0)
		return (parse_pipe(dyn, p));
	if (ft_strcmp((char *)*tokens, "<") == 0)
		return (parse_redir_in(dyn, envp, p, tokens));
	if (ft_strcmp((char *)*tokens, ">") == 0)
		return (parse_redir_out(dyn, envp, p, tokens));
	if (ft_strcmp((char *)*tokens, ">>") == 0)
		return (parse_redir_apnd(dyn, envp, p, tokens));
	if (ft_strcmp((char *)*tokens, "<<") == 0)
		return (parse_here_doc(dyn, p, tokens));
	return (parse_cmd_builtin(dyn, envp, p, tokens));
}

ssize_t	parse_pipe(t_list **dyn, t_phrase **ps)
{
	int			rw[2];

	if (!phrase_spawn(dyn, ps))
		return (-1);
	(*ps)->type = PIPE;
	if (pipe(rw) == -1)
		return (perror(gc_strjoin(dyn, MINISHELL, ": pipe")), -1);
	(*ps)->deb.pipe_ends = (t_pipe_rw){.read_end = rw[0], .write_end = rw[1]};
	return (1);
}
