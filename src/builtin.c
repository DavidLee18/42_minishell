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

int			exec_builtin(char *name, char **argv);
int			exec_echo(char **argv);
int			cd(char **argv);
int			pwd(char **argv);
int			exec_exit(char **argv);
