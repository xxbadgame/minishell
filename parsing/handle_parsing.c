/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:37:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/14 12:11:25 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../terminal.h"

int	handle_pipe_or_end(int *i, t_token *tokens_list, t_cmd **current)
{
    t_cmd *new_current;

    if (!tokens_list->next)
        return(0);
    new_current = create_cmd(count_elem_cmd(tokens_list->next));
    if (!new_current)
        return (-1);
    (*current)->next = new_current;
    (*current) = new_current;
    (*i) = 0;
    return (0);
}

int handle_word(int *i, t_token *tokens_list, t_cmd **current)
{
    (*current)->cmds[(*i)] = ft_strndup(tokens_list->value,ft_strlen(tokens_list->value));
    if (!(*current)->cmds[(*i)])
        return (-1);
    (*i)++;
    return (0);
}

int handle_redirection(t_cmd **current, t_token *tokens_list)
{
    if (tokens_list->type == REDIR_IN || tokens_list->type == REDIR_OUT)
    {
        if (for_redir((*current), tokens_list))
            return (-1);
        tokens_list = tokens_list->next;
    }
    else if (tokens_list->type == REDIR_APPEND)
    {
        if (for_append((*current), tokens_list))
            return (-1);
        tokens_list = tokens_list->next;
    }
    return (0);
}