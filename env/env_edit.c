/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:40:18 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/04/29 15:11:55 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
char	*ft_getenv(char *var_name, t_env *env)
{
	char	**env_variable;
	int		i;

	i = 0;
	while (env->env_cpy[i] != NULL)
	{
		env_variable = ft_split(env->env_cpy[i], '=');
		if (ft_strncmp(env_variable[0], var_name, ft_strlen(var_name)) == 0)
		{
			free_split(env_variable);
			return (env->env_cpy[i]);
		}
		free_split(env_variable);
		i++;
	}
	return (NULL);
}
*/

void ft_get_path(t_env *env)
{
	char 	*tmp;
	char	*new_path;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (env->env_cpy[i] != NULL)
	{
		if (ft_strncmp(env->env_cpy[i], "PATH=", 5) == 0)
		{
			free(env->env_cpy[i]);
			new_path = ft_strdup(env->path_edit[0]);
			while (env->path_edit[j])
			{
				tmp = new_path;
				new_path = ft_strjoin3(tmp, ':', env->path_edit[j++]);
				free(tmp);
			}
			env->env_cpy[i] = ft_strjoin("PATH=", new_path);
			free(new_path);
			return;
		}
		i++;
	}
}
