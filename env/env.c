/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:46:02 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/05 10:53:26 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**envcpy(char **envp)
{
	int		i;
	char	**env_cpy;

	i = 0;
	env_cpy = malloc(sizeof(char *) * (env_size(envp) + 1));
	if (!env_cpy)
		return (NULL);
	while (envp[i])
	{
		env_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

t_env	*init_env(char **envp)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env_cpy = envcpy(envp);
	return (env);
}