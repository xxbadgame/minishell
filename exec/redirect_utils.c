/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:14:19 by yannis            #+#    #+#             */
/*   Updated: 2025/06/19 09:59:47 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int has_redirection(t_cmd *cmd)
{
	return (cmd->infile || cmd->outfile || cmd->heredoc || cmd->append);
}

int checker_redirection_only(t_cmd *cmd,t_shell *shell, int *in_fd)
{
	if (cmd->cmd_args[0] == NULL && has_redirection(cmd))
	{
		handle_redirection_only(cmd, shell);
		if (*in_fd != 0)
			close(*in_fd);
		return (0);
	}
	return (1);
}

int is_append_or_not(t_cmd *cmd)
{
	int fd;
	
	if (cmd->outfile && cmd->append == 0)
	{
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open outfile"), -1);
		close(fd);
	}
	if (cmd->outfile && cmd->append == 1)
	{
		fd = open(cmd->infile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open append"), -1);
		close(fd);
	}
	return (0);
}
int handle_redirection_only(t_cmd *cmd, t_shell *shell)
{
	int fd;

	if(is_append_or_not(cmd) == -1)
		return (-1);
	if (cmd->infile && cmd->heredoc == 0)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			return (perror("open infile"), -1);
		close(fd);
	}
	if (cmd->infile && cmd->heredoc == 1)
	{
		int heredoc_fd = heredoc(cmd->infile, shell);
		if (heredoc_fd >= 0)
			close(heredoc_fd);
	}
	return (0);
}