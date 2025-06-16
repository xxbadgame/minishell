/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/06/16 16:13:37 by engiusep         ###   ########.fr       */
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
				printf("char : %c\n", str[*i]);
				temp = (*result);
				(*result) = ft_joinchar(temp, str[*i]);
				free(temp);
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

void cut_quote(char *str, int *i, int *j, char **result ,t_shell *shell)
{
	char *temp;
	char *var_in_env;
	int dollar_pos;
	int exit_quote;
	
	dollar_pos = 0;
	while (check_char(str, *i))
	{
		exit_quote = in_quote(str, i, result, shell);
		if (str[*i] == '\0')
			break;
		if (check_char2(str, *i) && exit_quote)
		{
			(*i)++;
			break;
		}
		else if(str[*i] == '$' && ft_isalpha(str[(*i) + 1]) == 0)
		{
			(*i) += 2;
		}
		else if (str[*i + 1] && str[*i] == '$' && str[*i + 1] == '?')
		{
			temp = (*result);
			(*result) = ft_strjoin(ft_strndup(temp, ft_strlen(temp)),ft_itoa(shell->last_exit));
			free(temp);
			(*i) += 2;
		}
		else if(str[*i] == '$' && env_var_checker(str + *i) != 0)
		{
			var_in_env = find_str_in_env(shell->env, ft_substr(str, *i, env_var_checker(str + *i)));
			if(!var_in_env)
			{
				(*i) += env_var_checker(str + *i);
				continue;
			}
			while(var_in_env[*j] && var_in_env[*j] != ' ')
			{
				temp = (*result);
				(*result) = ft_joinchar(temp, var_in_env[(*j)++]);
				free(temp);
			}
			if (var_in_env[*j] != '\0' && var_in_env[*j] == ' ')
			{
				(*j)++;
				break;
			}
			if (*j == ft_strlen(var_in_env))
				(*i) += env_var_checker(str + *i);
		}
		else
		{
			temp = (*result);
			(*result) = ft_joinchar(temp, str[*i]);
			free(temp);
			(*i)++;
		}
	}
}


