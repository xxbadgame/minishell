/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:20:00 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/11 14:33:04 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static void	handle_oldpwd(char *cwd, t_env *env)
{
	t_cmd	*cmd_2;

	cmd_2 = malloc(sizeof(t_cmd));
	cmd_2->cmd_args = malloc(sizeof(char *) * 3);
	cmd_2->cmd_args[0] = ft_strndup("export", 6);
	cmd_2->cmd_args[1] = ft_strjoin("OLDPWD=", cwd);
	cmd_2->cmd_args[2] = NULL;
	builtin_export(cmd_2, env);
	free(cmd_2->cmd_args[0]);
	free(cmd_2->cmd_args[1]);
	free(cmd_2);
}

static int	check_path_cmd(t_cmd *cmd)
{
	if (cmd->cmd_args[1] != NULL)
	{
		if (cmd->cmd_args[1][0] == '/')
		{
			if (chdir(cmd->cmd_args[1]) == -1)
				return (perror("dir"), -1);
			return (1);
		}
	}
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*cwd;
	char	*new_path;
	char	*temp;

	if (check_path_cmd(cmd) == -1)
		return (-1);
	else if (check_path_cmd(cmd) == 1)
		return (0);
	cwd = getcwd(NULL, 0);
	handle_oldpwd(cwd, env);
	new_path = ft_strjoin(cwd, "/");
	if (!new_path)
		return (free(cwd), -1);
	temp = new_path;
	if (cmd->cmd_args[1] != NULL)
		new_path = ft_strjoin(temp, cmd->cmd_args[1]);
	else
		new_path = find_str_in_env(env, "HOME");
	free(temp);
	if (!new_path)
		return (free(cwd), -1);
	if (chdir(new_path) == -1)
		return (free(cwd), free(new_path), perror("dir"), -1);
	return (free(new_path), free(cwd), 0);
}
