/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/07/03 10:55:26 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	in_quote_var_env(char **result, t_shell *shell, t_index_lexer *index,
		char *str)
{
	char	*temp[3];
	char	*var_in_env;

	temp[0] = (*result);
	temp[1] = ft_substr(str, index->i, env_var_checker(str + index->i));
	if (!temp[1])
		return (-1);
	var_in_env = find_str_in_env(shell->env, temp[1]);
	if (!var_in_env)
	{
		index->i += env_var_checker(str + index->i);
		return (free(temp[1]), 1);
	}
	temp[2] = ft_strndup(temp[0], ft_strlen(temp[0]));
	if (!temp[2])
		return (free(temp[1]), -1);
	(*result) = ft_strjoin(temp[2], var_in_env);
	if (!(*result))
		return (free(temp[1]), free(temp[2]), -1);
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(var_in_env);
	index->i += env_var_checker(str + index->i);
	return (0);
}

static	void	checker_micro_symbol(t_index_lexer *index, char *str)
{
	if (str[index->i] == '<' || str[index->i] == '>' || str[index->i] == '|')
		index->flag_symbole = 1;
}

int	double_quote_loop(char *str, t_index_lexer *index, char **result,
		t_shell *shell)
{
	int	count_quote;

	count_quote = 0;
	checker_micro_symbol(index, str);
	while (str[index->i] && str[index->i] != '"')
	{
		if (str[index->i] == '\'')
			count_quote++;
		if (check_lex_in_loop(str, index, result, shell) == 2)
			continue ;
	}
	return (count_quote);
}

int	simple_quote_loop(char *str, t_index_lexer *index, char **result)
{
	int	count_quote;

	count_quote = 0;
	checker_micro_symbol(index, str);
	while (str[index->i] && str[index->i] != '\'')
	{
		if (str[index->i] == '"')
			count_quote++;
		end_loop(result, str, index);
	}
	return (count_quote);
}
int	select_simple_double(char *str, t_index_lexer *index, char **result,
		t_shell *shell)
{
	int	counter;

	counter = 0;
	if (str[index->i] == '"')
	{
		index->i++;
		counter++;
		counter += double_quote_loop(str, index, result, shell);
		index->i++;
		counter++;
	}
	else if (str[index->i] == '\'')
	{
		index->i++;
		counter++;
		counter += simple_quote_loop(str, index, result);
		index->i++;
		counter++;
	}
	else
		end_loop(result,str, index);
	return (counter);
}

int	in_quote(char *str, t_index_lexer *index, char **result, t_shell *shell)
{
	int	first_round;
	int	count_total;
	int	counter;

	first_round = 0;
	counter = 0;
	if (str[index->i] == '\'' || str[index->i] == '"')
	{
		count_total = check_quote(str + index->i);
		index->i++;
		first_round = 1;
		while (str[index->i] && (str[index->i] != '\'' || str[index->i] != '"'
				|| str[index->i] != ' ') && counter != count_total)
		{
			if (first_round == 1)
			{
				index->i--;
				first_round = 0;
			}
			counter += select_simple_double(str, index, result, shell);
		}
		return (1);
	}
	return (0);
}

int	check_char(char *str, int i)
{
	if (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && ft_strncmp(str + i, ">>", 2) != 0 && ft_strncmp(str
			+ i, "<<", 2) != 0)
		return (1);
	return (0);
}

void	cut_quote(char *str, t_index_lexer *index, char **result,
		t_shell *shell)
{
	while (check_char(str, index->i))
	{
		if (start_loop(str, index, result, shell) == 1)
			break ;
		if (str[index->i + 1] && str[index->i] == '$' 
			&& ft_isalpha(str[index->i + 1]) == 0 && index->expand_heredoc == 0)
			index->i += 2;
		else if (str[index->i + 1] && str[index->i] == '$' 
			&& str[index->i + 1] == '?' && index->expand_heredoc == 0)
			after_dollar_checker(index, result, shell);
		else if (str[index->i + 1] && str[index->i] == '$'
			&& env_var_checker(str + index->i) != 0 && index->expand_heredoc == 0)
		{
			if (in_quote_var_env(result, shell, index, str) == 1)
				continue;
		}
		else
			end_loop2(result, str, index);
	}
}
