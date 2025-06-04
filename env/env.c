/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:46:02 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/04 13:25:55 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"


static int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void add_in_env(char **origin_env, char **dest_env, int *i)
{
	while (origin_env[*i])
	{
		dest_env[*i] = ft_strndup(origin_env[*i], ft_strlen(origin_env[*i]));
		if(!dest_env[*i])
			return (free_tab(dest_env));
		(*i)++;
	}
}

static char	**envcpy(char **envp)
{
	char	**env_cpy;
	int i;
	
	i = 0;
	env_cpy = malloc(sizeof(char *) * (env_size(envp) + 1));
	if (!env_cpy)
		return (NULL);
	add_in_env(envp, env_cpy, &i);
	env_cpy[i] = NULL;
	if (!env_cpy)
		return(free_tab(env_cpy),NULL);
	return (env_cpy);
}

t_env	*init_env(char **envp)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env_cpy = envcpy(envp);
	if(!env->env_cpy)
		return (free(env),NULL);
	return (env);
}