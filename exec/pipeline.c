/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:13:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:08 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static void	pipeline_exit_checker(t_shell *shell, int last_pid)
{
	int	status;
	int	waited_pid;
	int	flag_stop;

	flag_stop = 0;
	waited_pid = wait(&status);
	while (waited_pid > 0)
	{
		handle_sig_output(&flag_stop, status);
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				shell->last_exit = 128 + WTERMSIG(status);
				if (WCOREDUMP(status))
					write(2, "Quit (core dumped)\n", 20);
			}
		}
		waited_pid = wait(&status);
	}
	if (flag_stop == 1)
		write(1, "\n", 1);
}

int 	redirect_choice_pipe_infile(t_cmd *cmd, int *in_fd)
{
	if (cmd->heredoc == 1 && cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, 0) == -1)
			return (-1);
		close(cmd->heredoc_fd);
	}
	else if (cmd->infile != NULL)
		redirect_left(cmd->infile);
	else if (*in_fd != 0)
	{
		if (dup2(*in_fd, 0) == -1)
			return (-1);
		close(*in_fd);
	}
	return (0);
}

int 	redirect_choice_pipe_outfile(t_cmd *cmd, int *in_fd, int *pipefd)
{
	if (redirect_choice_pipe_infile(cmd, in_fd) == -1)
		return (-1);
	if (cmd->outfile && cmd->append == 0)
	{	
		if (redirect_right(cmd->outfile) == -1)
			return (-1);
	}
	else if (cmd->outfile && cmd->append == 1)
	{	
		if (double_redirect_right(cmd->outfile) == -1)
			return (-1);
	}
	else if (cmd->next)
	{
		if (dup2(pipefd[1], 1) == -1)
			return (-1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	return (0);
}

int	no_child_pipe(t_cmd *cmd, t_shell *shell, int *pipefd, int *in_fd)
{
	int	stdout_backup;
	int	builtin_no_child;

	if (is_child_builtin(cmd) == 1)
	{
		stdout_backup = dup(1);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		builtin_no_child = builtins_no_child(cmd, shell);
		dup2(stdout_backup, 1);
		close(stdout_backup);
		if (builtin_no_child == 0)
		{
			handle_next_pipe(in_fd, cmd, pipefd);
			return (0);
		}
		if (builtin_no_child == -1)
			return (-1);
	}
	return (1);
}

static int	pipe_loop(t_shell *shell, t_cmd *cmd, int *pid, int *in_fd)
{
	int	pipefd[2];
	int	flag_no_child_pipe;

	if (cmd->heredoc == 1)
		cmd->heredoc_fd = heredoc(cmd->infile, shell);
	if (cmd->next)
		pipe(pipefd);
	flag_no_child_pipe = no_child_pipe(cmd, shell, pipefd, in_fd);
	if (flag_no_child_pipe == 0)
		return (0);
	else if (flag_no_child_pipe == -1)
		return (-1);
	else
	{
		*pid = fork();
		if (*pid == 0)
		{
			if(signal_and_pipe_redirect(cmd, in_fd, shell, pipefd) == -1)
				return (-1);
		}
		return (handle_next_pipe(in_fd, cmd, pipefd), *pid);
	}
	return (0);
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
		if (checker_redirection_only(cmd, shell, &in_fd) == 0)
			return (0);
		last_pid = pipe_loop(shell, cmd, &pid, &in_fd);
		if (last_pid == -1)
			return (-1);
		cmd = cmd->next;
	}
	if (in_fd != 0)
		close(in_fd);
	signal(SIGINT, SIG_IGN);
	pipeline_exit_checker(shell, last_pid);
	signal(SIGINT, handle_sigint);
	return (0);
}
