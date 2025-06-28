/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:57:37 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/28 13:01:59 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	is_echo_n(const char *s)
{
	int	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	if (s[i] != 'n')
		return (0);
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

static void	print_echo_args(t_cmd *cmd, int i)
{
	int	first = 1;
	while (cmd->cmd_args[i])
	{
		if (!first)
			write(1, " ", 1);
		write(1, cmd->cmd_args[i], strlen(cmd->cmd_args[i]));
		first = 0;
		i++;
	}
}

int	builtin_echo(t_cmd *cmd)
{
	int	i = 1;
	int	newline = 1;

	while (cmd->cmd_args[i] && is_echo_n(cmd->cmd_args[i]))
	{
		newline = 0;
		i++;
	}
	print_echo_args(cmd, i);
	if (newline)
		write(1, "\n", 1);
	return (0);
}
