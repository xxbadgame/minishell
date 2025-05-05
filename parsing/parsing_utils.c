/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:40:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/05 15:44:05 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	for_redir(t_cmd *current, t_token *tmp)
{
    if (tmp->type == REDIR_IN && tmp->next && tmp->next->type == WORD)
    {
        current->infile = ft_strdup(tmp->next->value);
        if (!current->infile)
            return (1);
    }
    else if (tmp->type == REDIR_OUT && tmp->next && tmp->next->type == WORD)
    {
        current->outfile = ft_strdup(tmp->next->value);
        if (!current->outfile)
            return (1);
        current->append = 0;
    }
    else
    {
        write(2, "ERROR\n", 6);
        return (1);
    }
    return (0);
}

int	for_append(t_cmd *current, t_token *tmp)
{
    current->outfile = ft_strdup(tmp->value);
    if (!current->outfile)
        return (1);
    current->append = 1;
    return (0);
}

int	handle_pipe_or_end(int *argc, t_token **tmp, t_cmd **current)
{
    t_cmd *new_current;

    (*current)->argv[(*argc)] = NULL;
    new_current = init_cmd(count_elem_cmd((*tmp)->next));
    if (!new_current)
        return (1);
    (*current)->next = new_current;
    (*current) = new_current;
    (*argc) = 0;
    return (0);
}

int	command_checker(int *argc, t_token **tmp, t_cmd **current)
{
    if ((*tmp)->type == WORD)
    {
        (*current)->argv[(*argc)] = ft_strdup((*tmp)->value);
        if (!(*current)->argv[(*argc)])
            return (1);
        (*argc)++;
    }
    else if ((*tmp)->type == REDIR_IN || (*tmp)->type == REDIR_OUT)
    {
        if (for_redir((*current), (*tmp)))
            return (1);
        (*tmp) = (*tmp)->next;
    }
    else if ((*tmp)->type == REDIR_APPEND)
    {
        if (for_append((*current), (*tmp)))
            return (1);
        (*tmp) = (*tmp)->next;
    }
    else if ((*tmp)->type == PIPE || (*tmp)->next == NULL)
    {
        if (handle_pipe_or_end(argc, tmp, current))
            return (1);
    }
    return (0);
}
