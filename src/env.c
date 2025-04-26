/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:20:19 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/26 22:45:38 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
