/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/06/17 16:37:52 by engiusep         ###   ########.fr       */
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
void after_dollar_checker(t_index_lexer *index, char **result, t_shell *shell)
{
	char *temp[3];
	
	temp[0] = (*result);
	temp[1] = ft_strndup(temp[0], ft_strlen(temp[0]));
	if (!temp[1])
		return ;
	temp[2] = ft_itoa(shell->last_exit);
	if(!temp[2])
		return(free(temp[1]));
	(*result) = ft_strjoin(temp[1],temp[2]);
	if(!(*result))
		return(free(temp[1]),free(temp[2]));
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	index->i += 2;
}
void end_loop(char **result, char *str, t_index_lexer *index)
{
	char *temp;
	
	temp = (*result);
	(*result) = ft_joinchar(temp, str[index->i]);
	if(!(*result))
		return ;
	free(temp);
	index->i++;
}
int in_quote_var_env(char **result,t_shell *shell,t_index_lexer *index,char *str)
{
	char *temp[3];
	char *var_in_env;
	
	temp[0] = (*result);
	temp[1] = ft_substr(str, index->i, env_var_checker(str + index->i));
	if(!temp[1])
		return (-1);
	var_in_env = find_str_in_env(shell->env,temp[1]);
	if(!var_in_env)
	{
		index->i += env_var_checker(str + index->i);
		return (1);
	}
	temp[2] = ft_strndup(temp[0], ft_strlen(temp[0]));
	if(!temp[2])
		return(free(temp[1]),-1);
	(*result) = ft_strjoin(temp[2],var_in_env);
	if(!(*result))
		return(free(temp[1]),free(temp[2]),-1);
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(var_in_env);
	index->i += env_var_checker(str + index->i);
	return (0);
}
int in_quote(char *str,t_index_lexer *index, char **result ,t_shell *shell)
{
	if (str[index->i] == '"' || str[index->i] == '\'')
	{
		index->i++;
		while (str[index->i] && str[index->i] != '\'' && str[index->i] != '"')
		{
			if (str[index->i + 1] && str[index->i] == '$' && str[index->i + 1] == '?')
				after_dollar_checker(index,result,shell);
			else if(str[index->i] == '$' && ft_isalpha(str[index->i + 1]) == 0)
				index->i += 2;
			else if(str[index->i] == '$' && env_var_checker(str + index->i) != 0)
			{
				if(in_quote_var_env(result,shell,index,str)== 1)
					continue;
			}
			else
				end_loop(result,str,index);
		}
		index->i++;
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
		return (-1);
	while(var_in_env[index->j] && var_in_env[index->j] != ' ')
	{
		temp = (*result);
		(*result) = ft_joinchar(temp, var_in_env[(index->j)++]);
		if(!result)
			return (free(var_in_env),-1);
		free(temp);
	}
	if (var_in_env[index->j] != '\0' && var_in_env[index->j] == ' ')
	{
		(index->j)++;
		return (2);
	}
	if (index->j == ft_strlen(var_in_env))
		index->i += env_var_checker(str + index->i);
	free(var_in_env);
	return (0);
}

int start_loop(char *str, t_index_lexer *index, char **result, t_shell *shell)
{
	int exit_quote;
	
	exit_quote = in_quote(str, index, result, shell);
	if (str[index->i] == '\0' && exit_quote)
		return(2);
	if (check_char2(str, index->i) && exit_quote)
	{
		(index->i)++;
		return(2);
	}
	return(0);
}




void cut_quote(char *str, t_index_lexer *index, char **result ,t_shell *shell)
{
	int dollar_pos;
	int flag_var_env;
	
	dollar_pos = 0;
	while (check_char(str, index->i))
	{
		if (start_loop(str, index, result, shell) == 2)
			break;
		if(str[index->i + 1] && str[index->i] == '$' && ft_isalpha(str[index->i + 1]) == 0)
			index->i += 2;
		else if (str[index->i + 1] && str[index->i] == '$' && str[index->i + 1] == '?')
			after_dollar_checker(index,result,shell);
		else if(str[index->i + 1] && str[index->i] == '$' && env_var_checker(str + index->i) != 0)
		{
			flag_var_env = dollar_var_env(result,index,str,shell);
			if(flag_var_env == 1)
				continue;
			if(flag_var_env == 2)
				break;
		}
		else
			end_loop(result, str, index);
	}
}
