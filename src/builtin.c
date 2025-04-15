/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:07:08 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/14 17:10:55 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// STDIN_FILENO read_end
// STDOUT_FILENO wirte_end

int			exec_builtin(char *name, char **argv)
{
    (void)name;
    (void)argv;
    return (-1);
}
int			exec_echo(char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[0], "-n", 2) == 0)
			flag = 1;
		if (flag == 0 && !argv[i + 1])
		{
			printf("%s\n", argv[i]);
			break ;
		}
		else if (flag == 1 && !argv[i + 1])
		{
			printf("%s", argv[i]);
			break ;
		}
		printf("%s ", argv[i]);
		i++;
	}
	return (0);
}

int			cd(char **argv)
{
	return (chdir(argv[0]));
}

int			pwd(char **argv)
{
	if (getcwd(argv[0], ft_strlen(argv[0])) == NULL)
		return (-1);
	printf("%s\n", argv[0]);
	return (0);
}

int			exec_exit(char **argv)
{
	(void)argv;
	printf("exit\n");
	return (256);
}
