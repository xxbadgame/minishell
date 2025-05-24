/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:07:33 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 11:13:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int builtin_env(t_env *env,t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while(env->env_cpy[i])
	{
		if(ft_strchr(env->env_cpy[i],'=') != 0)
			printf("%s\n",env->env_cpy[i]);
		i++;
	}
	while (cmd->cmd_args[j])
	{
		if(ft_strchr(cmd->cmd_args[j],'=') != 0)
			printf("%s\n",cmd->cmd_args[j]);
		else
			return(perror("env"), -1);
		j++;
	}
	return (0);
}
