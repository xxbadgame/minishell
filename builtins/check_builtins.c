/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:06:45 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/14 13:29:41 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int is_builtin(t_cmd *cmd, t_env *env)
{
	if(ft_strncmp(cmd->cmds[0],"echo", 4) == 0)
		builtin_echo(cmd);
	if(ft_strncmp(cmd->cmds[0],"cd", 2) == 0)
		builtin_cd(cmd);
	if(ft_strncmp(cmd->cmds[0],"env", 3) == 0)
		builtin_env(env);
	if(ft_strncmp(cmd->cmds[0],"exit", 4) == 0)
		builtin_exit();
	if(ft_strncmp(cmd->cmds[0],"pwd", 4) == 0)
		builtin_pwd();
	if(ft_strncmp(cmd->cmds[0],"unset", 4) == 0)
		builtin_unset(cmd, env);
	return(0);
}
