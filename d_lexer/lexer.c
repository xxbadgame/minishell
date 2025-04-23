/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:20:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/04/16 15:54:36 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token    *create_token(char *str, t_token_type type)
{
    t_token *token;
    token = malloc(sizeof(t_token));
    if(!token)
        return (NULL);
    token->type = type;
    token->value = str;
    token->next = NULL;
    return (token);   
}

void    add_token(t_token **tokens_list,t_token *new_token)
{
    t_token *temp;
    
    if(!tokens_list || !new_token)
        return ;
    if(*tokens_list == NULL)
    {
        *tokens_list = new_token;
        return ;
    }
    temp = *tokens_list;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = new_token;
    return ;
}

t_token **lexer(t_token **tokens_list, char *str)
{
    int i;
    i = 0;
    
    while(str[i])
    {
        if(str[i] == ' ')
            i++;
        else if(str[i] == '|')
            ft_pipe(tokens_list, &i);
        else if(str[i] == '<' || str[i] == '>')
            ft_redir(str, tokens_list, &i);
        else if(ft_strncmp(str + i, "<<", 2) == 0 || ft_strncmp(str + i, ">>", 2) == 0)
            ft_heredoc_or_append(str, tokens_list, &i);
        else
            ft_read_word(tokens_list, str, &i);
    }
    return (tokens_list);
}

// int main()
// {
//     int i;
//     i = 0;
//    t_token **tokens;
//     tokens = malloc(sizeof(t_token *)); 
//     if(!tokens)
//         return 0;
//     lexer(tokens,"echo salut | grep ok");
//     t_token *temp;
//     temp = *tokens;
//    while(temp != NULL)
//    {
//         printf("token[%d], value %s, type %d\n",i, temp->value,temp->type);
//         i++;
//         temp = temp->next;
//    }
   
// }
