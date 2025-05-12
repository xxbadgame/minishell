/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:50:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/08 14:43:45 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

t_cmd	*create_cmd(int count_elem)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = malloc(sizeof(char *) * (count_elem + 1));
	if (!new_cmd->argv)
		return (free(new_cmd), NULL);
	new_cmd->append = 0;
	new_cmd->infile = NULL;
	new_cmd->next = NULL;
	new_cmd->outfile = NULL;
	return (new_cmd);
}

int	count_elem_cmd(t_token *current)
{
	t_token	*tmp;
	int		count_elem;

	tmp = current;
	count_elem = 0;
	while (tmp && tmp->type != PIPE)
	{
		count_elem++;
		tmp = tmp->next;
	}
	return (count_elem);
}

int	parsing_token(t_shell *shell)
{
	t_cmd	*current;
	int		argc;

	argc = 0;
	current = create_cmd(count_elem_cmd(shell->tokens));
	if(!current)
		return (-1);
	shell->cmds = current;
	while (shell->tokens)
	{
		if(command_checker(&argc, &(shell->tokens), &current) == -1)
		  	return(free_cmds(shell),free(current),free_tab(current->argv), -1);
	}
	return (0);
}
