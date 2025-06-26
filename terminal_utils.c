/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:08:09 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/26 14:49:13 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	init_shell(t_shell *shell)
{
	shell->line = NULL;
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->last_exit = 0;
}

int	check_next(t_cmd *cmd, t_shell *shell)
{
	if (cmd->next != NULL && cmd->next->cmd_args[0] == NULL)
	{
		if (cmd->next != NULL && cmd->next->cmd_args[0] == NULL
			&& cmd->next->heredoc == 1 && has_redirection(cmd->next))
		{
			cmd->next->heredoc_fd = heredoc(cmd->next->infile, shell);
			if (cmd->next->heredoc_fd == -1)
				return (-1);
		}
		else if (cmd->next != NULL && cmd->next->cmd_args[0] == NULL
			&& cmd->next->heredoc == 0 && has_redirection(cmd->next))
		{
			if (handle_redirection_only(cmd->next) == -1)
				return (-1);
		}
		return (0);
	}
	return (0);
}
