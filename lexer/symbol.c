/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:51:52 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/03 10:16:31 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	ft_read_word(t_token **tokens_list, char *str, t_index_lexer *index,
		t_shell *shell)
{
	t_token	*token;
	char	*result;

	result = malloc(1);
	if (!result)
		clean_and_exit(shell, 1);
	result[0] = '\0';
	token = NULL;
	cut_quote(str, index, &result, shell);
	token = create_token(result, WORD);
	if (!token)
		return (free(result), -1);
	add_token(tokens_list, token);
	index->expand_heredoc = 0;
	return (0);
}

int	ft_pipe(t_token **tokens_list, t_index_lexer *index)
{
	t_token	*token;
	char	*temp;

	index->j = 0;
	token = NULL;
	temp = ft_strndup("|", 1);
	if (!temp)
		return (-1);
	token = create_token(temp, PIPE);
	if (!token)
		return (free(temp), -1);
	add_token(tokens_list, token);
	(index->i)++;
	return (0);
}

int	ft_redir(char *str, t_token **tokens_list, int *i)
{
	t_token	*token;
	char	*temp;

	token = NULL;
	if (str[*i] == '<')
	{
		temp = ft_strndup("<", 1);
		if (!temp)
			return (-1);
		token = create_token(temp, REDIR_IN);
		if (!token)
			return (free(temp), -1);
	}
	else if (str[*i] == '>')
	{
		temp = ft_strndup(">", 1);
		if (!temp)
			return (-1);
		token = create_token(temp, REDIR_OUT);
		if (!token)
			return (free(temp), -1);
	}
	(*i)++;
	return (add_token(tokens_list, token), 0);
}

int	ft_heredoc_or_append(char *str, t_token **tokens_list, t_index_lexer *index)
{
	t_token	*token;
	char	*temp;

	token = NULL;
	temp = NULL;
	if (str[index->i] == '<' && str[index->i + 1] == '<')
	{
		temp = ft_strndup("<<", 2);
		if (!temp)
			return (-1);
		index->expand_heredoc = 1;
		token = create_token(temp, HEREDOC);
		if (!token)
			return (free(temp), -1);
	}
	else if ((str[index->i] == '>' && str[index->i + 1] == '>'))
	{
		temp = ft_strndup(">>", 2);
		if (!temp)
			return (-1);
		token = create_token(temp, REDIR_APPEND);
		if (!token)
			return (free(temp), -1);
	}
	index->i += 2;
	return (add_token(tokens_list, token), 0);
}
