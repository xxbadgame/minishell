/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:57:37 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/14 09:55:41 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd->cmds[1], "-n", 2) == 0 && i++)
	{
		while (cmd->cmds[i])
		{
			if (i > 2)
				printf(" %s", cmd->cmds[i++]);
			else
				printf("%s", cmd->cmds[i++]);
		}
	}
	else
	{
		while (cmd->cmds[i])
		{
			if (i > 1)
				printf(" %s", cmd->cmds[i++]);
			else
				printf("%s", cmd->cmds[i++]);
		}
		printf("\n");
	}
	return (0);
}
