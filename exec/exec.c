/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/06/19 09:29:45 by engiusep         ###   ########.fr       */
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

void	exec_choice(t_cmd *cmd, t_shell *shell)
{
	if (is_builtin(cmd) == 0)
		launch_execve(cmd, shell);
	else
		exec_builtin(cmd, shell);
}

void	redirect_choice_single(t_cmd *cmd, int heredoc_fd)
{
	if (cmd->heredoc == 1 && heredoc_fd != -1)
	{
		if(dup2(heredoc_fd, 0) == -1)
			return ;
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
	int builtin_no_child;

	heredoc_fd = -1;
	builtin_no_child = single_builtins_no_child(cmd, shell);
	if (builtin_no_child == 0)
		return (0);
	else if (builtin_no_child == -1)
		return (-1);
	if (cmd->heredoc == 1)
		heredoc_fd = heredoc(cmd->infile, shell);
	pid = fork();
	if (pid < 0)
		return (perror("pid"), -1);
	else if (pid == 0)
		signal_and_single_redirect(cmd, shell, heredoc_fd);
	if (heredoc_fd != -1)
		close(heredoc_fd);
	signal(SIGINT, SIG_IGN);
	single_exit_checker(shell);
	signal(SIGINT, handle_sigint);
	return (0);
}
