/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:40:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/05 09:42:26 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	handle_word(int *i, t_token *current_token, t_cmd **current_cmd, t_env *env)
{
	int	dollar;

	dollar = checker_dollar(current_token->value);
	if (dollar == 1)
	{
		(*current_cmd)->cmd_args[(*i)] = find_str_in_env(env,
				current_token->value);
		if ((*current_cmd)->cmd_args[(*i)] == NULL)
		{
			printf("\n");
			return (-1);
		}
		(*i)++;
		return (0);
	}
	(*current_cmd)->cmd_args[(*i)] = ft_strndup(current_token->value,
			ft_strlen(current_token->value));
	if (!(*current_cmd)->cmd_args[(*i)])
		return (-1);
	(*i)++;
	return (0);
}

int	handle_redirection(t_cmd **current_cmd, t_token *current_token)
{
	if (current_token->type == REDIR_IN || current_token->type == REDIR_OUT)
	{
		if (for_redir((*current_cmd), current_token))
			return (-1);
		current_token = current_token->next;
	}
	else if (current_token->type == REDIR_APPEND)
	{
		if (for_append((*current_cmd), current_token))
			return (-1);
		current_token = current_token->next;
	}
	else if (current_token->type == HEREDOC)
	{
		if (for_heredoc((*current_cmd), current_token))
			return (-1);
		current_token = current_token->next;
	}
	return (0);
}

int	handle_pipe_or_end(int *i, t_token *current_token, t_cmd **current_cmd)
{
	t_cmd	*new_current;

	if (!current_token->next)
		return (0);
	new_current = create_cmd(count_elem_cmd(current_token->next));
	if (!new_current)
		return (-1);
	(*current_cmd)->next = new_current;
	(*current_cmd) = new_current;
	(*i) = 0;
	return (0);
}

int	command_checker(int *i, t_token *current_token, t_cmd **current_cmd,
		t_env *env)
{
	if (current_token->type == WORD)
	{
		if (handle_word(i, current_token, current_cmd, env) == -1)
			return (-1);
	}
	else if (current_token->type == REDIR_IN || current_token->type == REDIR_OUT
		|| current_token->type == REDIR_APPEND
		|| current_token->type == HEREDOC)
	{
		if (handle_redirection(current_cmd, current_token) == -1)
			return (-1);
	}
	else if (current_token->type == PIPE || current_token->next == NULL)
	{
		if (handle_pipe_or_end(i, current_token, current_cmd) == -1)
			return (-1);
	}
	(*current_cmd)->cmd_args[(*i)] = NULL;
	return (0);
}
