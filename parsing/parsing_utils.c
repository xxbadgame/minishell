#include "parsing.h"

int    for_redir(t_cmd *current,t_token **tmp)
{
    *tmp = (*tmp)->next;
    if((*tmp)->type == REDIR_IN)
    {
        *tmp = (*tmp)->next;
        current->infile = ft_strdup((*tmp)->value);
    }
    else if(*tmp && (*tmp)->type == WORD)
    {
        current->outfile = ft_strdup((*tmp)->value);
        current->append = 0;
        *tmp = (*tmp)->next;
    }
    else
    {
        write(2,"ERROR\n",6);
        return (1);
    }
    return (0);
}

void    for_append(t_cmd *current, t_token **tmp)
{
    *tmp = (*tmp)->next;
    current->outfile = ft_strdup((*tmp)->value);
    current->append = 1;
}