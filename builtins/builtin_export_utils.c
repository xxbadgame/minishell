/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:00:41 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/18 13:06:19 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int checker_var_format(t_cmd *cmd, int i)
{
	char **spl;
	int j;

	spl = ft_split(cmd->cmd_args[i], '=');
	if (!spl || !spl[0])
		return (-1);
	j = 0;
	if (!ft_isalpha(spl[0][j]) && spl[0][j] != '_')
		return (free_tab(spl),-1);
	while (spl[0][j])
	{
		if (!ft_isalnum(spl[0][j]) && spl[0][j] != '_')
			return (free_tab(spl),-1);
		j++;
	}
	free_tab(spl);
	return (0);
}

int	find_var_env(t_cmd *cmd, char **env, int *j)
{
	int		i;
	char	**sub_cmd;
	char	**sub_env_var;

	i = 0;
	while (env[i])
	{
		sub_cmd = ft_split(cmd->cmd_args[*j], '=');
		if (!sub_cmd)
			return (-1);
		sub_env_var = ft_split(env[i], '=');
		if (!sub_env_var)
			return (free_tab(sub_cmd), -1);
		if (ft_strncmp(sub_cmd[0], sub_env_var[0],
				ft_strlen(sub_env_var[0])) == 0
			&& ft_strlen(sub_cmd[0]) == ft_strlen(sub_env_var[0]))
			return (free_tab(sub_cmd), free_tab(sub_env_var), i);
		free_tab(sub_cmd);
		free_tab(sub_env_var);
		i++;
	}
	return (-1);
}
