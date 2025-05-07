/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:40:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/07 10:39:57 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	for_redir(t_cmd *current, t_token *tmp)
{
    if (tmp->type == REDIR_IN && tmp->next && tmp->next->type == WORD)
    {
        current->infile = ft_strdup(tmp->next->value);
        if (!current->infile)
            return (-1);
    }
    else if (tmp->type == REDIR_OUT && tmp->next && tmp->next->type == WORD)
    {
        current->outfile = ft_strdup(tmp->next->value);
        if (!current->outfile)
            return (-1);
        current->append = 0;
    }
    else
    {
        write(2, "ERROR\n", 6);
        return (-1);
    }
    return (0);
}

int	for_append(t_cmd *current, t_token *tmp)
{
    current->outfile = ft_strdup(tmp->value);
    if (!current->outfile)
        return (-1);
    current->append = 1;
    return (0);
}

int command_checker(int *argc, t_token **tmp, t_cmd **current)
{
    if ((*tmp)->type == WORD)
    {
        if (handle_word(argc, tmp, current))
            return (-1);
    }
    else if ((*tmp)->type == REDIR_IN || (*tmp)->type == REDIR_OUT || (*tmp)->type == REDIR_APPEND)
    {
        if (handle_redirection(current, tmp))
            return (-1);
    }
    else if ((*tmp)->type == PIPE || (*tmp)->next == NULL)
    {
        if (handle_pipe_or_end(argc, tmp, current))
            return (-1);
    }
    (*current)->argv[(*argc)] = NULL;
    return (0);
}
