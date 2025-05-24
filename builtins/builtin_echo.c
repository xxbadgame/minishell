/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:57:37 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 11:13:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd->cmd_args[1], "-n", 2) == 0 && i++)
	{
		while (cmd->cmd_args[i])
		{
			if (i > 2)
				printf(" %s", cmd->cmd_args[i++]);
			else
				printf("%s", cmd->cmd_args[i++]);
		}
	}
	else
	{
		while (cmd->cmd_args[i])
		{
			if (i > 1)
				printf(" %s", cmd->cmd_args[i++]);
			else
				printf("%s", cmd->cmd_args[i++]);
		}
		printf("\n");
	}
	return (0);
}
