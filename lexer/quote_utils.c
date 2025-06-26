/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/06/26 15:35:57 by engiusep         ###   ########.fr       */
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
		return (1);
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

int	in_quote(char *str, t_index_lexer *index, char **result, t_shell *shell)
{
	if (str[index->i] == '"' || str[index->i] == '\'')
	{
		index->i++;
		while (str[index->i] && str[index->i] != '\'' && str[index->i] != '"')
		{
			if (str[index->i + 1] && str[index->i] == '$'
				&& str[index->i + 1] == '?')
				after_dollar_checker(index, result, shell);
			else if (str[index->i] == '$' && ft_isalpha(str[index->i + 1]) == 0)
				index->i += 2;
			else if (str[index->i] == '$'
				&& env_var_checker(str + index->i) != 0)
			{
				if (in_quote_var_env(result, shell, index, str) == 1)
					continue ;
			}
			else
				end_loop(result, str, index);
		}
		index->i++;
		return (1);
	}
	return (0);
}

int	check_char(char *str, int i)
{
	if (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && ft_strncmp(str + i, ">>", 2) != 0
		&& ft_strncmp(str + i, "<<", 2) != 0)
		return (1);
	return (0);
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

void	cut_quote(char *str, t_index_lexer *index, char **result,
		t_shell *shell)
{
	int	flag_var_env;

	while (check_char(str, index->i))
	{
		if (start_loop(str, index, result, shell) == 2)
			break ;
		if (str[index->i + 1] && str[index->i] == '$'
			&& ft_isalpha(str[index->i + 1]) == 0)
			index->i += 2;
		else if (str[index->i + 1] && str[index->i] == '$'
			&& str[index->i + 1] == '?')
			after_dollar_checker(index, result, shell);
		else if (str[index->i + 1] && str[index->i] == '$'
			&& env_var_checker(str + index->i) != 0)
		{
			flag_var_env = dollar_var_env(result, index, str, shell);
			if (flag_var_env == 1)
				continue ;
			if (flag_var_env == 2)
				break ;
		}
		else
			end_loop2(result, str, index);
	}
}
