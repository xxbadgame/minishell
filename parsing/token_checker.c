/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:40:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/12 06:47:52 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

static int	handle_word(int *i, t_token *current_token, t_cmd **current_cmd)
{
	(*current_cmd)->cmd_args[(*i)] = ft_strndup(current_token->value,
			ft_strlen(current_token->value));
	if (!(*current_cmd)->cmd_args[(*i)])
		return (-1);
	(*i)++;
	return (0);
}

static int	handle_redirection(t_cmd **current_cmd, t_token *current_token)
{
	if (current_token->type == REDIR_IN || current_token->type == REDIR_OUT)
	{
		if (for_redir((*current_cmd), current_token) == -1)
			return (-1);
	}
	else if (current_token->type == REDIR_APPEND)
	{
		if (for_append((*current_cmd), current_token) == -1)
			return (-1);
	}
	else if (current_token->type == HEREDOC)
	{
		if (for_heredoc((*current_cmd), current_token) == -1)
			return (-1);
	}
	return (0);
}

static int	handle_pipe(int *i, t_token *current_token, t_cmd **current_cmd)
{
	t_cmd	*new_current;

	new_current = create_cmd(count_elem_cmd(current_token->next));
	if (!new_current)
		return (-1);
	(*current_cmd)->next = new_current;
	(*current_cmd) = new_current;
	(*i) = 0;
	return (0);
}

int	command_checker(int *i, t_token **current_token, t_cmd **current_cmd)
{
	if ((*current_token)->type == WORD)
	{
		if (handle_word(i, (*current_token), current_cmd) == -1)
			return (-1);
		*current_token = (*current_token)->next;
	}
	else if ((*current_token)->type == REDIR_IN || (*current_token)->type == REDIR_OUT
		|| (*current_token)->type == REDIR_APPEND
		|| (*current_token)->type == HEREDOC)
	{
		if (handle_redirection(current_cmd, (*current_token)) == -1)
			return (-1);
		*current_token = (*current_token)->next;
		if ((*current_cmd)->cmd_args[0] != NULL)
			*current_token = (*current_token)->next;
	}
	else if ((*current_token)->type == PIPE)
	{
		if (handle_pipe(i, (*current_token), current_cmd) == -1)
			return (-1);
		*current_token = (*current_token)->next;
	}
	return (0);
}
