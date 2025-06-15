/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:14:19 by yannis            #+#    #+#             */
/*   Updated: 2025/06/15 06:20:41 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int has_redirection(t_cmd *cmd)
{
	return (cmd->infile || cmd->outfile || cmd->heredoc || cmd->append);
}

int handle_redirection_only(t_cmd *cmd, t_shell *shell)
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
