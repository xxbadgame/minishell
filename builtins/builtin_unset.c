/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:19:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/05 10:38:06 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static char	*unset_utils(t_env *env, t_cmd *cmd, int i, int *j)
{
	char	*new_var;

	new_var = NULL;
	if (ft_strncmp(env->env_cpy[i], cmd->cmd_args[1],
			ft_strlen(cmd->cmd_args[1])) != 0)
	{
		new_var = ft_strndup(env->env_cpy[i], ft_strlen(env->env_cpy[i]));
		if (!new_var)
			return (NULL);
		(*j)++;
	}
	return (new_var);
}

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	char	**new_env;
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy)));
	if (!new_env)
		return (-1);
	while (env->env_cpy[i])
	{
		new_env[j] = unset_utils(env, cmd, i, &j);
		if (!new_env)
			return (free_tab(new_env), -1);
		i++;
	}
	new_env[j] = NULL;
	temp = env->env_cpy;
	env->env_cpy = new_env;
	return (free_tab(temp), 0);
}
