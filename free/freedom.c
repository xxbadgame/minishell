/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:13:27 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 13:42:35 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

void free_env(t_env	*env)
{
	free_tab(env->env_cpy);
	free(env);
}

void free_tokens(t_token **tokens_list)
{
	t_token *token;
	t_token *token_tmp;

	token = *tokens_list;
	while (token)
	{
		free(token->value);	
		token_tmp = token;
		token = token->next;
		free(token_tmp);
	}
}

void free_cmds(t_cmd **cmds)
{
	t_cmd *cmd;
	t_cmd *cmd_tmp;

	cmd = *cmds;
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