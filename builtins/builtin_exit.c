/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:20:44 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/18 13:02:30 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_exit(t_shell *shell)
{
	int test;
	test = shell->last_exit;
	printf("exit\n");
	if(!shell->cmds->cmd_args[1])
	{
		free(shell->line);
		free_tokens(shell);
		free_cmds(shell);
		free_env(shell);
		test = shell->last_exit; 
		free(shell);
		exit(test);
	}
	else if (ft_isnum(shell->cmds->cmd_args[1])
		|| ft_atoi(shell->cmds->cmd_args[1]) == -1)
	{
		print_error("minishell: exit:", shell->cmds->cmd_args[1],
			" numeric argument required\n");
		test = 2;
	}
	else if(shell->cmds->cmd_args[2])
	{
		print_error("minishell: exit:", shell->cmds->cmd_args[1],
			" too many argument\n");
		test = 1;
		
	}
	else
		test = ft_atoi(shell->cmds->cmd_args[1]) % 256;
	free(shell->line);
	free_tokens(shell);
	free_cmds(shell);
	free_env(shell);
	free(shell);
	exit(test);
}

