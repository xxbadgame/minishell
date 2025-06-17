/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/06/17 10:49:00 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	check_quote(char *str)
{
	int	j;
	int	simple_quote;
	int	double_quote;

	double_quote = 0;
	simple_quote = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '\'')
			simple_quote++;
		if (str[j] == '"')
			double_quote++;
		j++;
	}
	if (simple_quote % 2 == 0 && double_quote % 2 == 0 && (simple_quote != 0
			|| double_quote != 0))
		return (simple_quote + double_quote);
	else if (simple_quote % 2 != 0 || double_quote % 2 != 0)
		return (-1);
	return (0);
}

int env_var_checker(char *str)
{
	int i;
	
	i = 0;
	if (str[0] == '$')
	{
		i++;
		while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\'' && str[i] != '"' && str[i] != '|' && str[i] != '>'
			&& str[i] != '<' && ft_strncmp(str + i, ">>", 2) != 0
			&& ft_strncmp(str + i, "<<", 2) != 0)
		{
			i++;
		}
		if (i == 1)
			return(0);
		return (i);
	}
	return (0);
} 

void clean_pointer(char *str, char **result)
{
	char *temp;
	
	temp = (*result);
	(*result) = str;
	free(temp);
}
int in_quote(char *str, int *i, char **result ,t_shell *shell)
{
	char *temp;
	char *var_in_env;
	
	if (str[*i] == '"' || str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'' && str[*i] != '"')
		{
			if (str[*i + 1] && str[*i] == '$' && str[*i + 1] == '?')
			{
				temp = (*result);
				(*result) = ft_strjoin(ft_strndup(temp, ft_strlen(temp)),ft_itoa(shell->last_exit));
				free(temp);
				(*i) += 2;
			}
			else if(str[*i] == '$' && ft_isalpha(str[(*i) + 1]) == 0)
			{
				(*i) += 2;
			}
			else if(str[*i] == '$' && env_var_checker(str + *i) != 0)
			{
				temp = (*result);
				var_in_env = find_str_in_env(shell->env, ft_substr(str, *i, env_var_checker(str + *i)));
				if(!var_in_env)
				{
					(*i) += env_var_checker(str + *i);
					continue;
				}
				(*result) = ft_strjoin(ft_strndup(temp, ft_strlen(temp)),var_in_env);
				free(temp);
				(*i) += env_var_checker(str + *i);
			}
			else
			{
				clean_pointer(ft_joinchar(temp, str[*i]), result);
				(*i)++;
			}
		}
		(*i)++;
		return(1);
	}
	return (0);
}

int check_char(char *str, int i)
{
	if(str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && ft_strncmp(str + i, ">>", 2) != 0
		&& ft_strncmp(str + i, "<<", 2) != 0)
		return (1);
	return(0);
}

int check_char2(char *str, int i)
{
	if(str[i] == ' ' || str[i] == '|' || str[i] == '>'
		|| str[i] == '<' || ft_strncmp(str + i, ">>", 2) == 0
		|| ft_strncmp(str + i, "<<", 2) == 0)
		return (1);
	return(0);
}
char *malloc_var_in_env(char *str,t_shell *shell,t_index_lexer *index)
{
	char *temp;
	char *var_in_env;
	temp =  ft_substr(str, index->i, env_var_checker(str + index->i));
	var_in_env = find_str_in_env(shell->env,temp);
	free(temp);
	if(!var_in_env)
	{
		index->i += env_var_checker(str + index->i);
		return (NULL);
	}
	return (var_in_env);
}
int	dollar_var_env(char **result, t_index_lexer *index,char *str, t_shell *shell)
{
	char *var_in_env;
	char *temp;
	var_in_env = malloc_var_in_env(str, shell ,index);
	if(!var_in_env)
		return (1);
	while(var_in_env[index->j] && var_in_env[index->j] != ' ')
	{
		temp = (*result);
		(*result) = ft_joinchar(temp, var_in_env[(index->j)++]);
		free(temp);
	}
	if (var_in_env[index->j] != '\0' && var_in_env[index->j] == ' ')
	{
		(index->j)++;
		return (2);
	}
	if (index->j == ft_strlen(var_in_env))
		index->i += env_var_checker(str + index->i);
	return (0);
}
void cut_quote(char *str, t_index_lexer *index, char **result ,t_shell *shell)
{
	char *temp;
	int dollar_pos;
	int exit_quote;
	int flag_var_env;
	
	dollar_pos = 0;
	while (check_char(str, index->i))
	{
		exit_quote = in_quote(str, &index->i, result, shell);
		if (str[index->i] == '\0')
			break;
		if (check_char2(str, index->i) && exit_quote)
		{
			(index->i)++;
			break;
		}
		else if(str[index->i] == '$' && ft_isalpha(str[index->i + 1]) == 0)
		{
			index->i += 2;
		}
		else if (str[index->i + 1] && str[index->i] == '$' && str[index->i + 1] == '?')
		{
			temp = (*result);
			(*result) = ft_strjoin(ft_strndup(temp, ft_strlen(temp)),ft_itoa(shell->last_exit));
			free(temp);
			index->i += 2;
		}
		else if(str[index->i] == '$' && env_var_checker(str + index->i) != 0)
		{
			flag_var_env = dollar_var_env(result,index,str,shell);
			if(flag_var_env == 1)
				continue;
			if(flag_var_env == 2)
				break;
		}
		else
		{
			temp = (*result);
			(*result) = ft_joinchar(temp, str[index->i]);
			free(temp);
			index->i++;
		}
	}
}


