/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:57:37 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/23 14:04:47 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static void	print_echo_args(t_cmd *cmd, int i, int min_index)
{
	while (cmd->cmd_args[i])
	{
		if (i > min_index)
			printf(" %s", cmd->cmd_args[i++]);
		else
			printf("%s", cmd->cmd_args[i++]);
	}
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->cmd_args[1])
	{
		printf("\n");
		return (0);
	}
	if (ft_strncmp(cmd->cmd_args[1], "-n", 2) == 0 && i++)
		print_echo_args(cmd, i, 2);
	else
	{
		print_echo_args(cmd, i, 1);
		printf("\n");
	}
	return (0);
}
