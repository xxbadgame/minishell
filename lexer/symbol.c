/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:51:52 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/28 14:00:23 by engiusep         ###   ########.fr       */
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

	while(str[j] && str[j] != ' ')
	{
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
	
	while (str[j] && str[j] != ' ' && str[j] != '|' && str[j] != '>'
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
int	ft_read_word(t_token **tokens_list, char *str, int *i,t_shell *shell)
{
	int		start;
	t_token	*token;
	char *result;
	int fisrt_quote;
	int last_quote;
	char *temp;
	
	fisrt_quote = -1;
	last_quote = -1;
	token = NULL;	
	if(check_quote(str, i) == 1)
	{
		start = *i;
		find_quote(str, i,&fisrt_quote,&last_quote);
	}
	else if (check_quote(str, i) == 0)
		start = *i;
	else
		return (-1);

	result = NULL;
	if(check_quote(str, i) == 1)
	{
		result = ft_substr(str, fisrt_quote + 1,last_quote - fisrt_quote - 1);

		while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>'
			&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
			&& ft_strncmp(str + *i, "<<", 2) != 0)
				(*i)++;
	}
	else if(check_quote(str, i) == 0)
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>'
			&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
			&& ft_strncmp(str + *i, "<<", 2) != 0)
				(*i)++;
		result = ft_strndup(str + start, *i - start);
		if(!result)
			return(-1);
	}
	if(ft_strncmp(result,"$?",2) == 0)
	{
		temp = result;
		result = ft_itoa(shell->last_exit);
		free(temp);
	}
	token = create_token(result, WORD);
	if(!token)
		return(free(result), -1);
	add_token(tokens_list, token);
	return (0);
}

int	ft_pipe(t_token **tokens_list, int *i)
{
	t_token	*token;
	char *temp;
	token = NULL;
	temp = ft_strndup("|", 1);
	if(!temp)
		return(-1);
	token = create_token(temp, PIPE);
	if(!token)
		return(free(temp),-1);
	add_token(tokens_list, token);
	(*i)++;
	return (0);
}

int	ft_redir(char *str, t_token **tokens_list, int *i)
{
	t_token	*token;
	char *temp;

	
	token = NULL;
	if (str[*i] == '<')
	{
		temp = ft_strndup("<", 1);
		if(!temp)
			return (-1);
		token = create_token(temp, REDIR_IN);
		if(!token)
			return(free(temp),-1);
	}
	else if (str[*i] == '>')
	{
		temp = ft_strndup(">", 1);
		if(!temp)
			return (-1);
		token = create_token(temp, REDIR_OUT);
		if(!token)
			return(free(temp),-1);
	}
	(*i)++;
	return (add_token(tokens_list, token),0);
}

int	ft_heredoc_or_append(char *str, t_token **tokens_list, int *i)
{
    t_token *token;
    char *temp;

    token = NULL;
    temp = NULL;
    if (str[*i] == '<' && str[*i + 1] == '<')
    {
        temp = ft_strndup("<<", 2);
        if (!temp)
            return (-1);
        token = create_token(temp, HEREDOC);
        if (!token)
            return (free(temp), -1);
    }
    else if ((str[*i] == '>' && str[*i + 1] == '>'))
    {
        temp = ft_strndup(">>", 2);
        if (!temp)
            return (-1);
        token = create_token(temp, REDIR_APPEND);
        if (!token)
            return (free(temp), -1);
    }
    (*i) += 2;
    return (add_token(tokens_list, token),0);
}
