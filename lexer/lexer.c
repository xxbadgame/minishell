/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:20:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 10:58:20 by yannis           ###   ########.fr       */
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

int conditional_lexer(t_token **tokens_list, char *str, int *i)
{
	if (str[*i] == ' ')
		(*i)++;
	else if (str[*i] == '|')
	{	
		if(ft_pipe(tokens_list, i) == -1)
			return (-1);
	}
	else if ((str[*i] == '<' && str[*i + 1] != '<') || (str[*i] == '>'  && str[*i + 1] != '>'))
	{
		if(ft_redir(str, tokens_list, i) == -1)
			return(-1);
	}
	else if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>'  && str[*i + 1] == '>'))
	{
		if(ft_heredoc_or_append(str, tokens_list, i) == -1)
			return (-1);
	}
	else
	{
		if(ft_read_word(tokens_list, str, i) == -1)
			return(-1);
	}
	return (0);
}

int lexer(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(conditional_lexer(&(shell->tokens), str, &i) == -1)
			return (-1);
	}
	return (0);
}
