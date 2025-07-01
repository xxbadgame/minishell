/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:06:45 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/01 14:51:19 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmd_args[0], "echo", 4) == 0
		&& ft_strlen(cmd->cmd_args[0]) == 4)
	{
		if (builtin_echo(cmd) == -1)
			return (-1);
	}
	else if (ft_strncmp(cmd->cmd_args[0], "env", 3) == 0
		&& ft_strlen(cmd->cmd_args[0]) == 3)
		builtin_env(shell->env, cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "pwd", 3) == 0
		&& ft_strlen(cmd->cmd_args[0]) == 3)
		builtin_pwd();
	else
		print_error("minishell: ", cmd->cmd_args[0], ": command not found\n");
	clean_and_exit(shell, 0);
	return (-1);
}

int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0
		|| ft_strncmp(cmd->cmd_args[0], "env", 3) == 0
		|| ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0
		|| ft_strncmp(cmd->cmd_args[0], "pwd", 3) == 0
		|| ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0
		|| ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
		return (1);
	return (0);
}

int	is_child_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0
		|| ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0
		|| ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
		return (1);
	return (0);
}
