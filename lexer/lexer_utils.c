/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:00:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/30 13:50:15 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	check_symbole_redirect(char *str, t_index_lexer *index)
{
	if (((str[index->i] == '<' && str[index->i + 1] != '<')
			|| (str[index->i] == '>' && str[index->i + 1] != '>')))
	{
		return (1);
	}
	return (0);
}

int	check_symbole_append_heredoc(char *str, t_index_lexer *index)
{
	if (((str[index->i] == '<' && str[index->i + 1] == '<')
			|| (str[index->i] == '>' && str[index->i + 1] == '>')))
		return (1);
	return (0);
}

int	checker_special_symbole(t_token *current)
{
	if ((ft_strncmp(current->value, ">", 1) == 0
			&& ft_strlen(current->value) == 1) || (ft_strncmp(current->value,
				"<", 1) == 0 && ft_strlen(current->value) == 1))
		return (1);
	if ((ft_strncmp(current->value, ">>", 2) == 0
			&& ft_strlen(current->value) == 2) || (ft_strncmp(current->value,
				"<<", 2) == 0 && ft_strlen(current->value) == 2))
		return (1);
	else if (ft_strncmp(current->value, "|", 1) == 0
		&& ft_strlen(current->value) == 1)
		return (2);
	return (0);
}

int	checker_flag_symbol(t_index_lexer *index, int flag_symbol, t_token *next,
		t_token *previous)
{
	if (flag_symbol == 1)
	{
		if (index->flag_symbole == 1)
		{
			index->flag_symbole = 0;
			return (0);
		}
		if (!next)
			return (-1);
		if (!previous && !next)
			return (-1);
	}
	else if (flag_symbol == 2)
	{
		if (index->flag_symbole == 1)
		{
			index->flag_symbole = 0;
			return (0);
		}
		if (!previous || !next || next->type != WORD)
			return (-1);
	}
	return (0);
}

int	primary_checker(char *line)
{
	int	i;
	int	code_primary_check;

	i = 0;
	while (line[i])
	{
		code_primary_check = primary_check_quote(line, &i);
		if (code_primary_check == 2)
			continue ;
		else if (code_primary_check == -1)
			return (-1);
		if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] != ' '
			&& !ft_isalnum(line[i + 1]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
		else if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != ' '
			&& !ft_isalnum(line[i + 1]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
		else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] != ' '
			&& !ft_isalnum(line[i + 2]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
		else if (line[i++] == '>' && line[i + 1] == '>' && line[i + 2] != ' '
			&& !ft_isalnum(line[i + 2]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
	}
	return (0);
}
