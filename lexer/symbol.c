/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:51:52 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 10:05:06 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	ft_read_word(t_token **tokens_list, char *str, int *i)
{
	int		start;
	t_token	*token;
	char *temp;
	
	token = NULL;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>'
		&& str[*i] != '<' && ft_strncmp(str + *i, ">>", 2) != 0
		&& ft_strncmp(str + *i, "<<", 2) != 0)
		(*i)++;
	temp = ft_strndup(str + start, *i - start);
	if(!temp)
		return(-1);
	token = create_token(temp, WORD);
	if(!token)
		return(free(temp),-1);
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
    if (ft_strncmp(str + *i, "<<", 2) == 0)
    {
        temp = ft_strndup("<<", 2);
        if (!temp)
            return (-1);
        token = create_token(temp, HEREDOC);
        if (!token)
            return (free(temp), -1);
    }
    else if (ft_strncmp(str + *i, ">>", 2) == 0)
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
