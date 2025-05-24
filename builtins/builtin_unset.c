/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:19:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 11:13:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_unset(t_cmd *cmd,t_env *env)
{
	char **new_env;
	char **temp;
	int i;
	int j;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy)));
	if(!new_env)
		return(-1);
	while(env->env_cpy[i])
	{
		if(ft_strncmp(env->env_cpy[i],cmd->cmd_args[1],ft_strlen(cmd->cmd_args[1])) != 0)
		{
			new_env[j] = ft_strndup(env->env_cpy[i], ft_strlen(env->env_cpy[i]));
			if(!new_env)
				return(free_tab(new_env), -1);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	temp = env->env_cpy;
	env->env_cpy = new_env;
	return (free_tab(temp), 0);
}
