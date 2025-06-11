/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:59 by yannis            #+#    #+#             */
/*   Updated: 2025/06/11 11:21:31 by engiusep         ###   ########.fr       */
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
void	cut_quote(char *str, int *i)
{
	int start;
	
	start = (*i);
	if (str[start] == '"' || str[start] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '|' && str[*i] != '>'
			&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
			&& ft_strncmp(str + *i, "<<", 2) != 0)
				(*i)++;
		(*i)++;
	}
	if(str[(*i)] != '"' && str[(*i)] != '\'')
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>'
			&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
			&& ft_strncmp(str + *i, "<<", 2) != 0)
				(*i)++;
	}
}


