/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:20:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/03 10:30:53 by yannis           ###   ########.fr       */
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
	int	code_read_word;
	int	special_result;

	if (str[index->i] == ' ' || str[index->i] == '\t')
		(index->i)++;
	else
	{
		special_result = handle_special_symbols(tokens_list, str, index);
		if (special_result == -1)
			return (-1);
		else if (special_result == 1)
		{
			code_read_word = ft_read_word(tokens_list, str, index, shell);
			if (code_read_word == -1)
				return (-1);
		}
	}
	return (0);
}

static int	synthax_checker(t_index_lexer *index, t_shell *shell)
{
	t_token	*previous;
	t_token	*current;
	t_token	*next;
	int		flag_symbol;

	previous = NULL;
	current = shell->tokens;
	next = shell->tokens->next;
	while (current)
	{
		flag_symbol = checker_special_symbole(current);
		if (checker_flag_symbol(index, flag_symbol, next, previous) == -1)
			return (-1);
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
	int				code_condi_lexer;

	index.i = 0;
	index.j = 0;
	index.flag_symbole = 0;
	index.expand_heredoc = 0;
	if (primary_checker(shell->line) == -1)
		return (-1);
	while (shell->line[index.i] != '\0')
	{
		code_condi_lexer = condi_lexer(&(shell->tokens), shell->line, &index,
				shell);
		if (code_condi_lexer == -1)
			return (-1);
		if (index.i > ft_strlen(shell->line))
			break ;
	}
	if (shell->tokens == NULL)
		return (0);
	if (synthax_checker(&index, shell) == -1)
	{
		ft_putendl_fd("minishell: synthax error", 2);
		return (-1);
	}
	return (0);
}
