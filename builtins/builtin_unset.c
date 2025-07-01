/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:19:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/01 14:42:16 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static void	end_unset(char **new_env, t_env *env, int j)
{
	char	**temp;

	new_env[j] = NULL;
	temp = env->env_cpy;
	env->env_cpy = new_env;
	free_tab(temp);
}

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	char	**new_env;
	int		i;
	int		j;

	if (!cmd->cmd_args[1])
		return (0);
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy) + 1));
	if (!new_env)
		return (-1);
	i = 0;
	j = 0;
	while (env->env_cpy[i])
	{
		if (!(ft_strncmp(cmd->cmd_args[1], env->env_cpy[i], ft_strlen(cmd->cmd_args[1])) == 0
			&& env->env_cpy[i][ft_strlen(cmd->cmd_args[1])] == '='))
		{
			new_env[j] = ft_strndup(env->env_cpy[i], ft_strlen(env->env_cpy[i]));
			if (!new_env[j])
				return (free_tab(new_env), -1);
			j++;
		}
		i++;
	}
	return (end_unset(new_env, env, j), 0);
}