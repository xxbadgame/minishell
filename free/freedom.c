/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:13:27 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 15:34:25 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

void free_env(t_shell **shell)
{
	if (!(*shell)->env)
		return;
	free_tab((*shell)->env->env_cpy);
	free((*shell)->env);
}

void free_tokens(t_shell **shell)
{
	t_token *token;
	t_token *token_tmp;

	if (!(*shell)->tokens)
		return;
	token = *((*shell)->tokens);
	while (token)
	{
		free(token->value);	
		token_tmp = token;
		token = token->next;
		free(token_tmp);
	}
}

void free_cmds(t_shell **shell)
{
	t_cmd *cmd;
	t_cmd *cmd_tmp;

	if (!(*shell)->cmds)
		return;
	cmd = *((*shell)->cmds);
	while (cmd)
	{
		free_tab(cmd->argv);
		free(cmd->infile);
		free(cmd->outfile);
		cmd_tmp = cmd;
		cmd = cmd->next;
		free(cmd_tmp);
	}
}