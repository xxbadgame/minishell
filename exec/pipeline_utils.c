/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:28:25 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/29 12:50:51 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

void	close_fd_exit(int *pipefd, int in_fd)
{
	close(pipefd[1]);
	close(pipefd[0]);
	if (in_fd != 0)
		close(in_fd);
}

int	pipe_loop(t_shell *shell, t_cmd *cmd, int *in_fd, int *pipefd)
{
	int	flag_no_child_pipe;

	flag_no_child_pipe = no_child_pipe(cmd, shell, pipefd, in_fd);
	if (flag_no_child_pipe == 0)
		return (0);
	else if (flag_no_child_pipe == -1)
		return (-1);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("fork"), -1);
	if (cmd->pid == 0)
	{
		if (signal_and_pipe_redirect(cmd, in_fd, shell, pipefd) == -1)
			return (-1);
	}
	handle_next_pipe(in_fd, cmd, pipefd);
	return (cmd->pid);
}

int	check_all_arg_for_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->heredoc == 1)
		{
			tmp->heredoc_fd = heredoc(tmp->infile, shell);
			if (tmp->heredoc_fd == -1)
				return (-1);
			if (tmp->next == NULL)
				close(tmp->heredoc_fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	creat_pipe(int *pipefd, t_cmd *cmd, int *last_pid)
{
	*last_pid = 0;
	if (cmd->next != NULL && cmd->next->cmd_args[0] != NULL)
	{
		if (pipe(pipefd) == -1)
			return (-1);
	}
	return (0);
}

int	exec_pipeline(t_cmd *cmd, int *pipefd, t_shell *shell, int *in_fd)
{
	int	redirect_only;
	int	last_pid;
	int	c_pipe;

	while (cmd)
	{
		c_pipe = creat_pipe(pipefd, cmd, &last_pid);
		if (c_pipe == -1)
			return (-1);
		redirect_only = checker_redirection_only(cmd);
		if (redirect_only == 0 && c_pipe == 0)
		{
			loop_exec_pipeline(&cmd, in_fd, pipefd);
			continue ;
		}
		else if (redirect_only == 0 && c_pipe == 1)
			return (last_pid);
		else if (redirect_only == -1)
			return (-1);
		last_pid = pipe_loop(shell, cmd, in_fd, pipefd);
		if (last_pid == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (last_pid);
}
