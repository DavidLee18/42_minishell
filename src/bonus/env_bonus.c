/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:21:37 by jaehylee          #+#    #+#             */
/*   Updated: 2025/05/01 22:23:30 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*env_join(t_list **dyn, char **envp)
{
	char	*str;
	int		i;

	i = 0;
	str = "";
	while (envp[i])
	{
		str = gc_strjoin(dyn, str, envp[i]);
		str = gc_strjoin(dyn, str, "\n");
		i++;
	}
	return (str);
}

char	**env_copy(t_list **dyn, char **envp)
{
	char	*str;

	str = env_join(dyn, envp);
	return (gc_split(dyn, str, '\n'));
}

void	reset_env(t_list **dyn, char ***envp, char *argv)
{
	char	*str;

	str = "";
	str = env_join(dyn, *envp);
	argv = gc_strjoin(dyn, "\n", argv);
	str = gc_strjoin(dyn, str, argv);
	*envp = gc_split(dyn, str, '\n');
}

void	export_print(t_list **dyn, char **envp)
{
	int		i;
	char	**ss;

	i = 0;
	ss = NULL;
	while (envp[i])
	{
		ss = gc_split(dyn, envp[i], '=');
		ft_fprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", ss[0], ss[1]);
		i++;
	}
}
