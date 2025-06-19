/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:20:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/19 15:06:36 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

t_token	*create_token(char *str, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = str;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens_list, t_token *new_token)
{
	t_token	*temp;

	temp = NULL;
	if (!tokens_list || !new_token)
		return ;
	if (*tokens_list == NULL)
	{
		*tokens_list = new_token;
		return ;
	}
	temp = *tokens_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
	return ;
}

static int	condi_lexer(t_token **tokens_list, char *str, t_index_lexer *index,
		t_shell *shell)
{
	if (str[index->i] == ' ' || str[index->i] == '\t')
		(index->i)++;
	else if (str[index->i] == '|')
	{
		if (ft_pipe(tokens_list, &index->i) == -1)
			return (-1);
	}
	else if (str[index->i + 1] && check_symbole_redirect(str, index) == 1)
	{
		if (ft_redir(str, tokens_list, &index->i) == -1)
			return (-1);
	}
	else if (str[index->i + 1] && check_symbole_append_heredoc(str, index) == 1)
	{
		if (ft_heredoc_or_append(str, tokens_list, &index->i) == -1)
			return (-1);
	}
	else
	{
		if (ft_read_word(tokens_list, str, index, shell) == -1)
			return (-1);
	}
	return (0);
}

static int	synthax_checker(t_shell *shell)
{
	t_token	*previous;
	t_token	*current;
	t_token	*next;
	int flag_symbol;

	previous = NULL;
	current = shell->tokens;
	next = shell->tokens->next;
	while (current)
	{
		flag_symbol = checker_special_symbole(current);
		if (flag_symbol == 1)
		{
			if (!next)
				return (-1);
			if (!previous && !next)
				return (-1);
		}
		else if (flag_symbol == 2)
		{
			if (!previous || !next)
				return (-1);
		}
		previous = current;
		if (next != NULL)
			next = next->next;
		current = current->next;
	}
	return (0);
}

int	lexer(t_shell *shell)
{
	t_index_lexer	index;

	index.i = 0;
	index.j = 0;
	while (shell->line[index.i])
	{
		if (condi_lexer(&(shell->tokens), shell->line, &index, shell) == -1)
			return (-1);
	}
	if (shell->tokens == NULL)
		return (-1);
	if (synthax_checker(shell) == -1)
	{
		printf("sythaxe error\n");
		return (-1);
	}
	return (0);
}
