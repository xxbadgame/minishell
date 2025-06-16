/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:20:44 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/16 12:55:09 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_exit(t_shell *shell)
{
	printf("exit\n");
	if (ft_isnum(shell->cmds->cmd_args[1]))
	{
		print_error("minishell: exit:", shell->cmds->cmd_args[1],
			" numeric argument required\n");
	}
	else
		shell->last_exit = ft_atoi(shell->cmds->cmd_args[1]) % 256;
	free(shell->line);
	free_tokens(shell);
	free_cmds(shell);
	free_env(shell);
	free(shell);
	exit(shell->last_exit);
}
