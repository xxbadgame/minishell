/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/06/04 13:56:22 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int check_quote(char *str, int *i)
{
	int j;
	int simple_quote;
	int double_quote;
	
	double_quote = 0;
	simple_quote = 0;
	j = *i;
	while (str[j])
	{
		if (simple_quote == 0 && double_quote == 0 && str[j] == ' ')
				break;
		if(str[j] == '\'')
			simple_quote++;
		if(str[j] == '"')
			double_quote++;
		j++;
	}
	if(simple_quote % 2 == 0 
		&& double_quote % 2 == 0 
		&& (simple_quote != 0 || double_quote != 0)) 
		return(1);
	else if(simple_quote % 2 != 0 || double_quote % 2 != 0)
		return (-1);
	return (0);
}

int find_quote(char *str,int *i ,int *fisrt_quote, int *last_quote)
{
	int j;
	
	j = *i;
	while (str[j] && str[j] != '|' && str[j] != '>'
		&& str[j] != '<' && ft_strncmp(str + j, ">>", 2) != 0
		&& ft_strncmp(str + j, "<<", 2) != 0)
	{
		if(str[j] == '\'' || str[j] == '"')
		{
			if(*fisrt_quote == -1)
				*fisrt_quote = j;
			*last_quote = j;
			j++;
			continue;
		}
		j++;
	}
	return (0);
}

char *loop_with_quote(char *str, int *i)
{
	char *result;
	int fisrt_quote;
	int last_quote;
	
	fisrt_quote = -1;
	last_quote = -1;
	find_quote(str, i,&fisrt_quote,&last_quote);
	result = ft_substr(str, fisrt_quote + 1,last_quote - fisrt_quote - 1);
	while (str[*i] && str[*i] != '|' && str[*i] != '>'
		&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
		&& ft_strncmp(str + *i, "<<", 2) != 0)
			(*i)++;
	return(result);
}

char *loop_without_quote(char *str, int *i)
{
	int		start;
	
	char *result;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>'
		&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
		&& ft_strncmp(str + *i, "<<", 2) != 0)
			(*i)++;
	result = ft_strndup(str + start, *i - start);
	if(!result)
		return(NULL);
	return(result);
}
