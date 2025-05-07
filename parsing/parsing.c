/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:50:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 10:06:45 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

t_cmd	*init_cmd(int count_elem)
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

t_cmd	**parsing_token(t_token **tokens_list)
{
	t_cmd	**cmds;
	t_token	*tmp;
	t_cmd	*current;
	int		argc;

	argc = 0;
	tmp = *tokens_list;
	current = init_cmd(count_elem_cmd(tmp));
	if(!current)
		return (NULL);
	cmds = malloc(sizeof(t_cmd *));
	if(!cmds)
		return(free(current),free_tab(current->argv),NULL);
	*cmds = current;
	while (tmp)
	{
		if(command_checker(&argc, &tmp, &current) == -1)
			return(free(cmds),free(current),free_tab(current->argv),NULL);
		tmp = tmp->next;
	}
	return (cmds);
}
