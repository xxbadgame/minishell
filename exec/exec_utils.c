/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:36:03 by yannis            #+#    #+#             */
/*   Updated: 2025/06/05 09:41:34 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static int	path_len(char *path_env, char *cmd)
{
	int	len_path_env;
	int	len_cmd;
	int	size_path;

	len_path_env = ft_strlen(path_env);
	len_cmd = ft_strlen(cmd);
	size_path = len_path_env + 1 + len_cmd + 1;
	return (size_path);
}

static char	*get_path_command(char *cmd)
{
	char	**all_path;
	char	*path;
	int		i;

	i = 0;
	all_path = ft_split(getenv("PATH"), ':');
	while (all_path[i])
	{
		path = malloc(path_len(all_path[i], cmd));
		if (!path)
			return (free_tab(all_path), NULL);
		path[0] = '\0';
		ft_strncat(path, all_path[i], ft_strlen(all_path[i]) + 1);
		ft_strncat(path, "/", ft_strlen(all_path[i]) + 2);
		ft_strncat(path, cmd, path_len(all_path[i], cmd));
		if (access(path, X_OK) == 0)
			return (free_tab(all_path), path);
		free(path);
		i++;
	}
	free_tab(all_path);
	return (NULL);
}

int	launch_execve(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (access(cmd->cmd_args[0], X_OK) == 0)
	{
		if (execve(cmd->cmd_args[0], cmd->cmd_args, env->env_cpy) == -1)
		{
			perror("exec failed");
			exit(EXIT_FAILURE);
		}
		return (0);
	}
	path = get_path_command(cmd->cmd_args[0]);
	if (execve(path, cmd->cmd_args, env->env_cpy) == -1)
	{
		perror("exec failed");
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (0);
}

void	handle_next_pipe(int *in_fd, t_cmd *cmd, int *pipefd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}
