/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:07:33 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/01 14:42:48 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_env(t_env *env, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if(cmd->cmd_args[1] != NULL)
	{
		print_error("env:",cmd->cmd_args[1],": No such file or directory\n");
		return (-1);
	}
	while (env->env_cpy[i])
	{
		if (ft_strchr(env->env_cpy[i], '=') != 0)
			printf("%s\n", env->env_cpy[i]);
		i++;
	}
	while (cmd->cmd_args[j])
	{
		if (ft_strchr(cmd->cmd_args[j], '=') != 0)
			printf("%s\n", cmd->cmd_args[j]);
		else
			return (perror("env"), -1);
		j++;
	}
	return (0);
}
