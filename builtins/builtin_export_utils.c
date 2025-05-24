/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:00:41 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 11:29:56 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	find_var_env(t_cmd *cmd, char **env, int *j)
{
	int		i;
	char	**sub_cmd;
	char	**sub_env_var;

	i = 0;
	while (env[i])
	{
		sub_cmd = ft_split(cmd->cmd_args[*j], '=');
		sub_env_var = ft_split(env[i], '=');
		if (ft_strncmp(sub_cmd[0], sub_env_var[0],
				ft_strlen(sub_env_var[0])) == 0
			&& ft_strlen(sub_cmd[0]) == ft_strlen(sub_env_var[0]))
		{
			free_tab(sub_cmd);
			free_tab(sub_env_var);
			return (i);
		}
		free_tab(sub_cmd);
		free_tab(sub_env_var);
		i++;
	}
	return (-1);
}
