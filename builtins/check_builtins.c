/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:06:45 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 11:13:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if(ft_strncmp(cmd->cmd_args[0],"echo", 4) == 0)
		builtin_echo(cmd);
	if(ft_strncmp(cmd->cmd_args[0],"env", 3) == 0)
		builtin_env(shell->env,cmd);
	if(ft_strncmp(cmd->cmd_args[0],"pwd", 3) == 0)
		builtin_pwd();
	free_tokens(shell);
	free_cmds(shell);
	free_env(shell);
	free(shell);
	exit(EXIT_SUCCESS);
	return(0);
}

int is_builtin(t_cmd *cmd)
{
	if(ft_strncmp(cmd->cmd_args[0],"echo", 4) == 0
	|| ft_strncmp(cmd->cmd_args[0],"cd", 2) == 0
	|| ft_strncmp(cmd->cmd_args[0],"env", 3) == 0
	|| ft_strncmp(cmd->cmd_args[0],"exit", 4) == 0
	|| ft_strncmp(cmd->cmd_args[0],"pwd", 3) == 0
	|| ft_strncmp(cmd->cmd_args[0],"unset", 5) == 0
	|| ft_strncmp(cmd->cmd_args[0],"export", 6) == 0
	)
		return(1);
	return(0);
}