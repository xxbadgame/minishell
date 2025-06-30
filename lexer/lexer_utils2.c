/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:40:18 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/30 14:20:00 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	handle_special_symbols(t_token **tokens_list, char *str,
		t_index_lexer *index)
{
	if (str[index->i] == '|')
	{
		if (ft_pipe(tokens_list, index) == -1)
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
		return (1);
	return (0);
}

int	primary_check_quote(char *line, int *i)
{
	char	quote;

	quote = '\0';
	if (line[*i] == ';')
	{
		ft_putendl_fd("not interpret ';'", 2);
		return (-1);
	}
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (!line[*i])
			return (ft_putendl_fd("minishell: unclose quote", 2), -1);
		(*i)++;
		return (2);
	}
	return (0);
}
