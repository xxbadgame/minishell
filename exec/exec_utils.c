/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:36:03 by yannis            #+#    #+#             */
/*   Updated: 2025/06/18 13:55:06 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	path_len(char *path_env, char *cmd)
{
	int	len_path_env;
	int	len_cmd;
	int	size_path;

	len_path_env = ft_strlen(path_env);
	len_cmd = ft_strlen(cmd);
	size_path = len_path_env + 1 + len_cmd + 1;
	return (size_path);
}

static char	*get_path_command(char *cmd, t_env *env)
{
	char	**all_path;
	char	*path_in_env;
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	path_in_env = find_str_in_env(env, "PATH");
	if (!path_in_env)
		return (NULL);
	all_path = ft_split(path_in_env, ':');
	free(path_in_env);
	if (!all_path)
		return (NULL);
	while (all_path[i])
	{
		path = cat_path(all_path, i, cmd);
		if (access(path, X_OK) == 0)
			return (free_tab(all_path), path);
		free(path);
		i++;
	}
	free_tab(all_path);
	return (NULL);
}

void	clean_and_exit(t_shell *shell, char *path, int status)
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
	char	*path;

	path = NULL;
	if (cmd->cmd_args[0] && access(cmd->cmd_args[0], X_OK) == 0)
	{
		execve(cmd->cmd_args[0], cmd->cmd_args, shell->env->env_cpy);
		perror("exec failed");
		clean_and_exit(shell, path, 126);
	}
	else if (cmd->cmd_args[0])
	{
		path = get_path_command(cmd->cmd_args[0], shell->env);
		if (path != NULL)
		{
			execve(path, cmd->cmd_args, shell->env->env_cpy);
			perror("exec failed");
			clean_and_exit(shell, path, 126);
		}
	}
	print_error("minishell: ", cmd->cmd_args[0], ": command not found\n");
	clean_and_exit(shell, path, 127);
	return (-1);
}

void	handle_next_pipe(int *in_fd, t_cmd *cmd, int *pipefd)
{
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}
