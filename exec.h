/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:57:12 by yannis            #+#    #+#             */
/*   Updated: 2025/05/06 13:55:06 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h"

typedef struct s_cmd
{
	int				index;
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;

}					t_cmd;

void free_split(char **split);
int pipeline(t_cmd **cmds, char **envp);
int	launch_execve(t_cmd *cmd, char **envp);
int ft_listlen(t_cmd **cmds);

#endif