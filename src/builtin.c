/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:07:08 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/14 21:02:53 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char *name, char **argv)
{
	(void)name;
	(void)argv;
	return (-1);
}

int	exec_echo(char **argv)
{
	(void)argv;
	return (-1);
}

int	cd(char **argv)
{
	(void)argv;
	return (-1);
}

int	pwd(char **argv)
{
	(void)argv;
	return (-1);
}

int	exec_exit(char **argv)
{
	(void)argv;
	return (-1);
}
