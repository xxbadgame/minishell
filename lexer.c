/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laxer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:20:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/04/16 14:47:10 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laxer.h"

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
    int i;
    t_token *temp;
    i = 0;
    
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
char   *read_word(char *str, int *i)
{
    int start;
    start = *i;
    while(str[*i] && str[*i] != ' ' && str[*i] != '|')
    {
        (*i)++;
    }
    return(ft_strndup(str + start,*i - start));
}
t_token **lexer(t_token **tokens_list, char *str)
{
    int i;
    t_token *token;
    token = NULL;
    i = 0;
    
    while(str[i])
    {
        if(str[i] == ' ')
            i++;
        else if(str[i] == '|')
        {
            token = create_token("|",PIPE);
            add_token(tokens_list,token);
            i++;
        }
        else
        {
            token = create_token(read_word(str, &i),WORD);
            add_token(tokens_list,token);
        }
        token = NULL;
    }
    return (tokens_list);
}

int main(int argc,char **argv, char **env)
{
    int i;
    i = 0;
    t_token **tokens;
    tokens = malloc(sizeof(t_token *));
    lexer(tokens,"echo salut | grep ok");
    t_token *temp;
    temp = *tokens;
   while(temp != NULL)
   {
        printf("token[%d], value %s, type %d\n",i, temp->value,temp->type);
        i++;
        temp = temp->next;
   }
}
