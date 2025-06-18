/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:46:02 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/18 13:23:11 by engiusep         ###   ########.fr       */
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

int	add_in_env(char **origin_env, char **dest_env, int *i)
{
	while (origin_env[*i])
	{
		dest_env[*i] = ft_strndup(origin_env[*i], ft_strlen(origin_env[*i]));
		if (!dest_env[*i])
			return (free_tab(dest_env), -1);
		(*i)++;
	}
	dest_env[*i] = NULL;
	return (0);
}

static char	**envcpy(char **envp)
{
	char	**env_cpy;
	int		i;

	i = 0;
	env_cpy = malloc(sizeof(char *) * (env_size(envp) + 1));
	if (!env_cpy)
		return (NULL);
	if (add_in_env(envp, env_cpy, &i) == -1)
		return (free_tab(env_cpy), NULL);
	env_cpy[i] = NULL;
	if (!env_cpy)
		return (free_tab(env_cpy), NULL);
	return (env_cpy);
}

t_env	*init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env_cpy = envcpy(envp);
	if (!env->env_cpy)
		return (free(env), NULL);
	return (env);
}
