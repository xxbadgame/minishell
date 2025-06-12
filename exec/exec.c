/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/06/12 10:34:18 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static int	single_builtins_no_child(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0
		&& ft_strlen(cmd->cmd_args[0]) == 4)
		builtin_exit(shell);
	if (ft_strncmp(cmd->cmd_args[0], "export", 6) == 0
		&& ft_strlen(cmd->cmd_args[0]) == 6)
		return (builtin_export(cmd, shell->env));
	if (ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0
		&& ft_strlen(cmd->cmd_args[0]) == 5)
		return (builtin_unset(cmd, shell->env));
	if (ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0
		&& ft_strlen(cmd->cmd_args[0]) == 2 )
	{
		if(cmd->cmd_args[2] != NULL)
		{
			printf("cd : to many arguments\n");
			return (0);
		}
		return (builtin_cd(cmd, shell->env));
	}
	return (1);
}

static void	single_exit_checker(t_shell *shell)
{
	int	sig;
	int	status;

	wait(&status);
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
}

static void	single_exec_choice(t_cmd *cmd, t_shell *shell)
{
	if (is_builtin(cmd) == 0)
		launch_execve(cmd, shell->env);
	else
		exec_builtin(cmd, shell);
	exit(0);
}

static void	redirect_choice_single(t_cmd *cmd, int heredoc_fd)
{
	if (cmd->heredoc == 1 && heredoc_fd != -1)
	{
		dup2(heredoc_fd, 0);
		close(heredoc_fd);
	}
	else if (cmd->infile != NULL && cmd->heredoc == 0)
		redirect_left(cmd->infile);
	if (cmd->outfile != NULL && cmd->append == 0)
		redirect_right(cmd->outfile);
	else if (cmd->outfile != NULL && cmd->append == 1)
		double_redirect_right(cmd->outfile);
}

int	exec_single_command(t_cmd *cmd, t_shell *shell)
{
	int	pid;
	int heredoc_fd;

	heredoc_fd = -1;
	if (single_builtins_no_child(cmd, shell) == 0)
		return (0);
	else if (single_builtins_no_child(cmd, shell) == -1)
		return (-1);
	if (cmd->heredoc == 1)
		heredoc_fd = heredoc(cmd->infile);
	pid = fork();
	if (pid < 0)
		return (perror("pid"), -1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirect_choice_single(cmd, heredoc_fd);
		single_exec_choice(cmd, shell);
	}
	if (heredoc_fd != -1)
		close(heredoc_fd);
	signal(SIGINT, SIG_IGN);
	single_exit_checker(shell);
	signal(SIGINT, handle_sigint);
	return (0);
}
