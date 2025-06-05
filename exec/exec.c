/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/06/05 09:41:38 by engiusep         ###   ########.fr       */
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
		&& ft_strlen(cmd->cmd_args[0]) == 2)
		return (builtin_cd(cmd, shell->env));
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
	if (cmd->infile != NULL && cmd->heredoc == 0)
		redirect_left(cmd->infile);
	else if (cmd->infile != NULL && cmd->heredoc == 1)
		heredoc(cmd->infile);
	if (cmd->outfile != NULL && cmd->append == 0)
		redirect_right(cmd->outfile);
	else if (cmd->outfile != NULL && cmd->append == 1)
		double_redirect_right(cmd->outfile);
	if (is_builtin(cmd) == 0)
		launch_execve(cmd, shell->env);
	else
		exec_builtin(cmd, shell);
	exit(0);
}

int	exec_single_command(t_cmd *cmd, t_shell *shell)
{
	int	pid;

	if (single_builtins_no_child(cmd, shell) == 0)
		return (0);
	else if (single_builtins_no_child(cmd, shell) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (perror("pid"), -1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		single_exec_choice(cmd, shell);
	}
	signal(SIGINT, SIG_IGN);
	single_exit_checker(shell);
	signal(SIGINT, handle_sigint);
	return (0);
}
