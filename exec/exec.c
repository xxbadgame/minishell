/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/05/24 18:52:51 by yannis           ###   ########.fr       */
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

int	exec_single_command(t_cmd *cmd, t_shell *shell, int flag_builtin)
{
	int	pid;
	int status;
	int sig;

	if (ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0)
		builtin_exit(shell);
	if (ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
		return (builtin_export(cmd, shell->env), 0);
	if (ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0)
		return (builtin_unset(cmd, shell->env), 0);
	if (ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0)
		builtin_cd(cmd,shell->env);
	pid = fork();
	if (pid < 0)
		return (perror("pid"), -1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd->infile != NULL && cmd->heredoc == 0)
			redirect_left(cmd->infile);
		else if (cmd->infile != NULL && cmd->heredoc == 1)
			heredoc(cmd->infile);
		if (cmd->outfile != NULL && cmd->append == 0)
			redirect_right(cmd->outfile);
		else if (cmd->outfile != NULL && cmd->append == 1)
			double_redirect_right(cmd->outfile);
		if (flag_builtin == 0)
			launch_execve(cmd, shell->env);
		else
			exec_builtin(cmd, shell);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		shell->last_exit = 128 + sig;
		if (sig == SIGINT)
			write(1, "\n", 1);
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)\n", 20);
	}
	signal(SIGINT, handle_sigint);
	return (0);
}
