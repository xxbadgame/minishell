/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:36:03 by yannis            #+#    #+#             */
/*   Updated: 2025/06/13 12:08:19 by yannis           ###   ########.fr       */
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

void clean_and_exit(t_shell *shell, char *path, int status)
{
	if (path)
		free(path);
	free(shell->line);
	free_tokens(shell);
	free_cmds(shell);
	free_env(shell);
	free(shell);
	exit(status);
}

int	launch_execve(t_cmd *cmd, t_shell *shell)
{
	char	*path = NULL;

	if (cmd->cmd_args[0] && access(cmd->cmd_args[0], X_OK) == 0)
	{
		execve(cmd->cmd_args[0], cmd->cmd_args, shell->env->env_cpy);
		perror("exec failed");
		exit(EXIT_FAILURE);
	}
	else if (cmd->cmd_args[0])
	{
		path = get_path_command(cmd->cmd_args[0]);
		if (path != NULL)
		{
			execve(path, cmd->cmd_args, shell->env->env_cpy);
			perror("exec failed");
			clean_and_exit(shell, path, 126);
		}
	}
	print_error("minishell: ",cmd->cmd_args[0], ": command not found\n");
	clean_and_exit(shell, path, 127);
	return (-1);
}

void handle_next_pipe(int *in_fd, t_cmd *cmd, int *pipefd, int heredoc_fd)
{
	if (heredoc_fd != -1)
		close(heredoc_fd);
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}
