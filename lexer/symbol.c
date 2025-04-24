/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:51:52 by engiusep          #+#    #+#             */
/*   Updated: 2025/04/16 16:03:02 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_read_word(t_token **tokens_list, char *str, int *i)
{
	int		start;
	t_token	*token;

	token = NULL;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>'
		&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
		&& ft_strncmp(str + *i, "<<", 2) != 0)
		(*i)++;
	token = create_token(ft_strndup(str + start, *i - start), WORD);
	add_token(tokens_list, token);
}

void	ft_pipe(t_token **tokens_list, int *i)
{
	t_token	*token;

	token = NULL;
	token = create_token(ft_strndup("|",1), PIPE);
	add_token(tokens_list, token);
	(*i)++;
}

void	ft_redir(char *str, t_token **tokens_list, int *i)
{
	t_token	*token;

	token = NULL;
	if (str[*i] == '<')
		token = create_token(ft_strndup("<", 1), REDIR_IN);
	else if (str[*i] == '>')
		token = create_token(ft_strndup(">", 1), REDIR_OUT);
	add_token(tokens_list, token);
	(*i)++;
}

void	ft_heredoc_or_append(char *str, t_token **tokens_list, int *i)
{
	t_token *token;

	token = NULL;
	if (ft_strncmp(str + *i, "<<", 2) == 0)
		token = create_token(ft_strndup("<<", 2), HEREDOC);
	else if (ft_strncmp(str + *i, ">>", 2) == 0)
		token = create_token(ft_strndup(">>", 2), REDIR_APPEND);
	add_token(tokens_list, token);
	(*i) += 2;
}