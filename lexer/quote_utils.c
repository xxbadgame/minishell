/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/06/11 15:38:29 by engiusep         ###   ########.fr       */
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

int env_var(char *str)
{
	int i;
	
	i = 0;
	if (str[0] == '$')
	{
		i++;
		while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"' && str[i] != '|' && str[i] != '>'
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

void cut_quote(char *str, int *i, char **result ,t_shell *shell)
{
	int start;
	char *temp;
	char *var_in_env;
	
	start = (*i);
	if (str[start] == '"' || str[start] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '|' && str[*i] != '>'
			&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
			&& ft_strncmp(str + *i, "<<", 2) != 0)
			{
				if (str[*i + 1] && str[*i] == '$' && str[*i + 1] == '?')
				{
					temp = (*result);
					(*result) = ft_strjoin(ft_strndup(temp, ft_strlen(temp)),ft_itoa(shell->last_exit));
					free(temp);
					(*i) += 2;
				}
				else if(env_var(str + *i) != 0)
				{
					temp = (*result);
					var_in_env = find_str_in_env(shell->env, ft_substr(str, *i, env_var(str + *i)));
					if(!var_in_env)
					{
						(*i) += env_var(str + *i);
						continue;
					}
					(*result) = ft_strjoin(ft_strndup(temp, ft_strlen(temp)),var_in_env);
					free(temp);
					(*i) += env_var(str + *i);
				}
				else
				{
					temp = (*result);
					(*result) = ft_joinchar(temp, str[*i]);
					free(temp);
					(*i)++;
				}
			}
		(*i)++;
	}
	if(str[(*i)] != '"' && str[(*i)] != '\'')
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>'
			&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
			&& ft_strncmp(str + *i, "<<", 2) != 0)
			{
				if (str[*i] == '$' && str[*i + 1] == '?')
				{
					temp = (*result);
					(*result) = ft_strjoin(ft_strndup(temp, ft_strlen(temp)),ft_itoa(shell->last_exit));
					free(temp);
					(*i) += 2;
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
}


