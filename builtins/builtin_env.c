/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:07:33 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/19 13:16:54 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int builtin_env(t_env *env,t_cmd *cmd)
{
	int i;
	i = 0;
	
	while(env->env_cpy[i])
	{
		if(ft_strchr(env->env_cpy[i],'=') != 0)
			printf("%s\n",env->env_cpy[i]);
		i++;
	}
	if(cmd->cmds[1] != NULL)
		printf("%s\n",cmd->cmds[1]);
	return (1);
}
