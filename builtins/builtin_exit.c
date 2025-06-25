/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:20:44 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/25 16:19:14 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static int	check_exit(int temp, t_shell *shell)
{
	if (!shell->cmds->cmd_args[1])
	{
		free(shell->line);
		free_tokens(shell);
		free_cmds(shell);
		free_env(shell);
		temp = shell->last_exit;
		free(shell);
		exit(temp);
	}
	return (0);
}

static void	free_exit(t_shell *shell)
{
	free(shell->line);
	free_tokens(shell);
	free_cmds(shell);
	free_env(shell);
	free(shell);
}

int	builtin_exit(t_shell *shell)
{
	int	temp;

	temp = shell->last_exit;
	printf("exit\n");
	check_exit(temp, shell);
	if (ft_isnum(shell->cmds->cmd_args[1])
		|| ft_atoi(shell->cmds->cmd_args[1]) == -1)
	{
		print_error("minishell: exit:", shell->cmds->cmd_args[1],
			" numeric argument required\n");
		temp = 2;
	}
	else if (shell->cmds->cmd_args[2])
	{
		print_error("minishell: exit:", shell->cmds->cmd_args[1],
			" too many argument\n");
		temp = 1;
	}
	else
		temp = ft_atoi(shell->cmds->cmd_args[1]) % 256;
	free_exit(shell);
	exit(temp);
}
