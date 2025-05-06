/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:12:56 by yannis            #+#    #+#             */
/*   Updated: 2025/05/06 13:41:35 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
}

int ft_listlen(t_cmd **cmds)
{
    int i;
    t_cmd *cmd;

    i = 0;
    cmd = *cmds;
    while (cmd)
    {
        cmd = cmd->next;
        i++;
    }
    return (i);
}