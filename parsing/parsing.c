/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:50:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 15:06:32 by engiusep         ###   ########.fr       */
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

t_cmd	**parsing_token(t_shell **shell)
{
	t_token	*tmp;
	t_cmd	*current;
	int		argc;

	argc = 0;
	tmp = *((*shell)->tokens);
	
	current = init_cmd(count_elem_cmd(tmp));
	if(!current)
		return (NULL);
	(*shell)->cmds = malloc(sizeof(t_cmd *));
	if(!(*shell)->cmds)
		return(free(current),free_tab(current->argv),NULL);
	*((*shell)->cmds) = current;
	while (tmp)
	{
		if(command_checker(&argc, &tmp, &current) == -1)
			return(free((*shell)->cmds),free(current),free_tab(current->argv),NULL);
		tmp = tmp->next;
	}
	return ((*shell)->cmds);
}
