/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:00:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/26 15:47:53 by engiusep         ###   ########.fr       */
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
	if (ft_strncmp(current->value, ">", 1) == 0 || (ft_strncmp(current->value,
				"<", 1) == 0 && ft_strlen(current->value) == 1))
		return (1);
	if (ft_strncmp(current->value, ">>", 2) == 0 || (ft_strncmp(current->value,
				"<<", 2) == 0 && ft_strlen(current->value) == 1))
		return (1);
	else if (ft_strncmp(current->value, "|", 1) == 0
		&& ft_strlen(current->value) == 1)
		return (2);
	return (0);
}

int	checker_flag_symbol(int flag_symbol, t_token *next, t_token *previous)
{
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
	return (0);
}

int	primary_checker(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if(line[i] == '\'' || line[i] == '"')
		{
			i++;
			while(line[i] && (line[i] != '\'' || line[i] != '"'))
				i++;
			i++;
		}
		if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] != ' '
			&& !ft_isalnum(line[i + 1]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
		else if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != ' '
			&& !ft_isalnum(line[i + 1]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
		else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] != ' '
			&& !ft_isalnum(line[i + 2]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
		else if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] != ' '
			&& !ft_isalnum(line[i + 2]))
			return (ft_putendl_fd("minishell: synthax error", 2), -1);
		i++;
	}
	return (0);
}
