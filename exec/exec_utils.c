/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:00:12 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 12:15:20 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../terminal.h"

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
