/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:13:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/05 09:41:43 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static int	pipeline_builtins_no_child(t_cmd *cmd, t_shell *shell)
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

static void	pipeline_exit_checker(t_shell *shell, int pid, int last_pid)
{
	int	sig;
	int	status;

	while (wait(&status) > 0)
	{
		if (pid == last_pid)
		{
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
	}
}

static void	pipeline_exec_choice(t_cmd *cmd, t_shell *shell, int *pipefd,
		int in_fd)
{
	if (cmd->infile != NULL && cmd->heredoc == 0)
		redirect_left(cmd->infile);
	else if (cmd->infile != NULL && cmd->heredoc == 1)
		heredoc(cmd->infile);
	else if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (cmd->outfile != NULL && cmd->append == 0)
		redirect_right(cmd->outfile);
	else if (cmd->outfile != NULL && cmd->append == 1)
		double_redirect_right(cmd->outfile);
	else if (cmd->next)
	{
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (is_builtin(cmd) == 0)
		launch_execve(cmd, shell->env);
	else
		exec_builtin(cmd, shell);
}

static int	pipe_loop(t_shell *shell, t_cmd *cmd, int *pid, int *in_fd)
{
	int	pipefd[2];

	pipeline_builtins_no_child(cmd, shell);
	if (cmd->next)
		pipe(pipefd);
	*pid = fork();
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipeline_exec_choice(cmd, shell, pipefd, *in_fd);
		exit(0);
	}
	handle_next_pipe(in_fd, cmd, pipefd);
	return (*pid);
}

int	pipeline(t_shell *shell)
{
	int		pid;
	int		last_pid;
	int		in_fd;
	t_cmd	*cmd;

	pid = 0;
	last_pid = 0;
	in_fd = 0;
	cmd = shell->cmds;
	while (cmd)
	{
		last_pid = pipe_loop(shell, cmd, &pid, &in_fd);
		cmd = cmd->next;
	}
	signal(SIGINT, SIG_IGN);
	pipeline_exit_checker(shell, pid, last_pid);
	signal(SIGINT, handle_sigint);
	return (0);
}
