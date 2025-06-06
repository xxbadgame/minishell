/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:50:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/06 14:18:33 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

t_cmd	*create_cmd(int count_elem)
{
	t_cmd	*new_cmd;
	int i;

	i = 0;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_args = malloc(sizeof(char *) * (count_elem + 1));
	if (!new_cmd->cmd_args)
		return (free(new_cmd), NULL);
	while (i < (count_elem + 1))
		new_cmd->cmd_args[i++] = NULL;
	new_cmd->append = 0;
	new_cmd->heredoc = 0;
	new_cmd->infile = NULL;
	new_cmd->next = NULL;
	new_cmd->outfile = NULL;
	return (new_cmd);
}

int	count_elem_cmd(t_token *current_token)
{
	t_token	*tmp;
	int		count_elem;

	tmp = current_token;
	count_elem = 0;
	while (tmp && tmp->type == WORD)
	{
		count_elem++;
		tmp = tmp->next;
	}
	return (count_elem);
}

int	parsing_token(t_shell *shell)
{
	t_cmd	*current_cmd;
	t_token	*current_token;
	int		i;

	i = 0;
	current_cmd = create_cmd(count_elem_cmd(shell->tokens));
	if (!current_cmd)
		return (-1);
	current_token = shell->tokens;
	shell->cmds = current_cmd;
	while (current_token)
	{
		if (command_checker(&i, &current_token, &current_cmd, shell->env) == -1)
			return (-1);
	}
	return (0);
}
