/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:13:27 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/13 11:48:55 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

void	free_env(t_shell *shell)
{
	if (!shell->env)
		return ;
	free_tab(shell->env->env_cpy);
	free(shell->env);
}

void	free_tokens(t_shell *shell)
{
	t_token	*token;
	t_token	*token_tmp;

	if (!shell->tokens)
		return ;
	token = shell->tokens;
	while (token)
	{
		token_tmp = token->next;
		free(token->value);
		free(token);
		token = token_tmp;
	}
	shell->tokens = NULL;
}

void	free_cmds(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*cmd_tmp;

	if (!shell->cmds)
		return ;
	cmd = shell->cmds;
	while (cmd)
	{
		cmd_tmp = cmd->next;
		if (cmd->heredoc_fd != -1)
			close(cmd->heredoc_fd);
		free_tab(cmd->cmd_args);
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		cmd = cmd_tmp;
	}
	shell->cmds = NULL;
}
