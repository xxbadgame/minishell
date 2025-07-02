/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:59 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/02 15:55:32 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	check_quote_simple(char *str)
{
	int	j;
	int	simple_quote;

	simple_quote = 0;
	j = 0;
	while (str[j] && (str[j] != ' ' || simple_quote % 2 != 0))
	{
		if (str[j] == '\'')
			simple_quote++;
		j++;
	}
	return (simple_quote);
}

int	check_quote_double(char *str)
{
	int	j;
	int	double_quote;

	double_quote = 0;
	j = 0;
	while (str[j] && (str[j] != ' ' || double_quote % 2 != 0))
	{
		if (str[j] == '"')
			double_quote++;
		j++;
	}
	return (double_quote);
}

int	check_quote(char *str)
{
	int	j;
	int	simple_quote;
	int	double_quote;
	char c_first;

	double_quote = 0;
	simple_quote = 0;
	j = 0;
	c_first = str[j];
	while (str[j])
	{
		if (str[j] == '\'')
			simple_quote++;
		if (str[j] == '"')
			double_quote++;
		if (c_first == '"')
		{
			if (str[j] == ' ' && double_quote % 2 != 0)
				j++;
			else if (str[j] == ' ' && double_quote % 2 == 0)
				break;
		}
		else if (c_first == '\'')
		{
			if (str[j] == ' ' && simple_quote % 2 != 0)
				j++;
			else if (str[j] == ' ' && simple_quote % 2 == 0)
				break;
		}
		j++;
	}
	return (simple_quote + double_quote);
}

int	env_var_checker(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
	{
		i++;
		while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\''
			&& str[i] != '"' && str[i] != '|' && str[i] != '>' && str[i] != '<'
			&& ft_strncmp(str + i, ">>", 2) != 0
			&& ft_strncmp(str + i, "<<", 2) != 0)
		{
			i++;
		}
		if (i == 1)
			return (0);
		return (i);
	}
	return (0);
}

void	after_dollar_checker(t_index_lexer *index, char **result,
		t_shell *shell)
{
	char	*temp[3];

	temp[0] = (*result);
	temp[1] = ft_strndup(temp[0], ft_strlen(temp[0]));
	if (!temp[1])
		return ;
	temp[2] = ft_itoa(shell->last_exit);
	if (!temp[2])
		return (free(temp[1]));
	(*result) = ft_strjoin(temp[1], temp[2]);
	if (!(*result))
		return (free(temp[1]), free(temp[2]));
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	index->i += 2;
}

void	end_loop(char **result, char *str, t_index_lexer *index)
{
	char	*temp;

	temp = (*result);
	(*result) = ft_joinchar(temp, str[index->i]);
	if (!(*result))
		return ;
	free(temp);
	index->i++;
}

void	end_loop2(char **result, char *str, t_index_lexer *index)
{
	char	*temp;

	if (str[index->i] == ';')
	{
		index->i++;
		return ;
	}
	temp = (*result);
	(*result) = ft_joinchar(temp, str[index->i]);
	if (!(*result))
		return ;
	free(temp);
	index->i++;
}
