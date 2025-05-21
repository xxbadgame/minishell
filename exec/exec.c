/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/05/21 12:54:45 by engiusep         ###   ########.fr       */
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

char	*get_path_command(char *cmd)
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

	path = get_path_command(cmd->cmds[0]);
	if (execve(path, cmd->cmds, env->env_cpy) == -1)
	{
		perror("exec failed");
		free(path);
		exit(-1);
	}
	free(path);
	return (0);
}

int	exec_single_command(t_cmd *cmd, t_shell *shell, int flag_builtin)
{
	int	pid;

	if (ft_strncmp(cmd->cmds[0], "exit", 4) == 0)
		builtin_exit(shell);
	if (ft_strncmp(cmd->cmds[0], "export", 6) == 0)
		return (builtin_export(cmd, shell->env), 0);
	if (ft_strncmp(cmd->cmds[0], "unset", 5) == 0)
		return (builtin_unset(cmd, shell->env), 0);
	if (ft_strncmp(cmd->cmds[0], "cd", 2) == 0)
		builtin_cd(cmd);
		
	pid = fork();
	if (pid < 0)
		return (perror("pid"), -1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd->outfile != NULL && cmd->append == 0)
			redirect_right(cmd->outfile);
		else if (cmd->outfile != NULL && cmd->append == 1)
			double_redirect_right(cmd->outfile);
		if (flag_builtin == 0)
			launch_execve(cmd, shell->env);
		else
		{
			if (exec_builtin(cmd, shell) == -1)
				return (-1);
		}
	}
	signal(SIGINT, SIG_IGN);
	int status;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)\n", 20);
	}
	signal(SIGINT, handle_sigint);
	return (0);
}
