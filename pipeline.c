/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:31 by yannis            #+#    #+#             */
/*   Updated: 2025/05/06 10:55:48 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int pipeline(t_cmd **cmds, char **envp)
{
    int pipe[2];
    t_cmd *cmd;
    
    cmd = *cmds;
    while (cmd != NULL)
    {
        execute_command(cmd, envp);
        
        cmd = cmd->next;
    }
    
}