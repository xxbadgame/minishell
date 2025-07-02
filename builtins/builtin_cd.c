/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:20:00 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/02 09:45:29 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static int	handle_oldpwd(char *cwd, t_env *env)
{
	t_cmd	*cmd_2;

	cmd_2 = malloc(sizeof(t_cmd));
	if (!cmd_2)
		return (-1);
	cmd_2->cmd_args = malloc(sizeof(char *) * 3);
	if (!cmd_2->cmd_args)
		return (free(cmd_2), -1);
	cmd_2->cmd_args[0] = ft_strndup("export", 6);
	if (!cmd_2->cmd_args[0])
		return (free(cmd_2->cmd_args), free(cmd_2), -1);
	cmd_2->cmd_args[1] = ft_strjoin("OLDPWD=", cwd);
	if (!cmd_2->cmd_args[1])
		return (free(cmd_2->cmd_args[0]), free(cmd_2->cmd_args), free(cmd_2),
			-1);
	cmd_2->cmd_args[2] = NULL;
	if (builtin_export(cmd_2, env) == -1)
		return (free(cmd_2->cmd_args[0]), free(cmd_2->cmd_args), free(cmd_2),
			-1);
	return (free(cmd_2->cmd_args[0]), free(cmd_2->cmd_args[1]),
		free(cmd_2->cmd_args[2]), free(cmd_2->cmd_args), free(cmd_2), 0);
}

static int	handle_pwd(t_env *env)
{
	t_cmd	*cmd_2;
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (-1);
	cmd_2 = malloc(sizeof(t_cmd));
	if (!cmd_2)
		return (-1);
	cmd_2->cmd_args = malloc(sizeof(char *) * 3);
	if (!cmd_2->cmd_args)
		return (free(cmd_2), -1);
	cmd_2->cmd_args[0] = ft_strndup("export", 6);
	if (!cmd_2->cmd_args[0])
		return (free(cmd_2->cmd_args), free(cmd_2), -1);
	cmd_2->cmd_args[1] = ft_strjoin("PWD=", temp);
	if (!cmd_2->cmd_args[1])
		return (free(cmd_2->cmd_args[0]), free(cmd_2->cmd_args), free(cmd_2),
			-1);
	cmd_2->cmd_args[2] = NULL;
	if (builtin_export(cmd_2, env) == -1)
		return (free(cmd_2->cmd_args[0]), free(cmd_2->cmd_args), free(cmd_2),
			-1);
	return (free(temp), free(cmd_2->cmd_args[0]), free(cmd_2->cmd_args[1]),
		free(cmd_2->cmd_args[2]), free(cmd_2->cmd_args), free(cmd_2), 0);
}

static int	check_path_cmd(t_cmd *cmd)
{
	if (cmd->cmd_args[1] == NULL)
		return (0);
	if (cmd->cmd_args[2] != NULL)
		return (ft_putendl_fd("cd : to many arguments", 2), -1);
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

static int	end_cd(char *cwd, t_env *env, t_cmd *cmd)
{
	char	*new_path;
	char	*temp;

	if (handle_oldpwd(cwd, env) == -1)
		return (free(cwd), -1);
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
	if (handle_pwd(env) == -1)
		return (-1);
	free(new_path);
	free(cwd);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*cwd;
	char	*new_path;

	if (check_path_cmd(cmd) == 1)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("cd: error retrieving current directory", 2);
		new_path = find_str_in_env(env, "OLDPWD");
		if (!new_path)
			return (-1);
		if (chdir(new_path) == -1)
			return (free(new_path), perror("dir"), -1);
		if (handle_pwd(env) == -1)
			return (-1);
		free(new_path);
	}
	else
	{
		if (end_cd(cwd, env, cmd) == -1)
			return (-1);
	}
	return (0);
}
