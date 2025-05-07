/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:37:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 10:39:46 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../terminal.h"

int	handle_pipe_or_end(int *argc, t_token **tmp, t_cmd **current)
{
    t_cmd *new_current;

    (*current)->argv[(*argc)] = NULL;
    new_current = init_cmd(count_elem_cmd((*tmp)->next));
    if (!new_current)
        return (-1);
    (*current)->next = new_current;
    (*current) = new_current;
    (*argc) = 0;
    return (0);
}

int handle_word(int *argc, t_token **tmp, t_cmd **current)
{
    (*current)->argv[(*argc)] = ft_strdup((*tmp)->value);
    if (!(*current)->argv[(*argc)])
        return (-1);
    (*argc)++;
    return (0);
}

int handle_redirection(t_cmd **current, t_token **tmp)
{
    if ((*tmp)->type == REDIR_IN || (*tmp)->type == REDIR_OUT)
    {
        if (for_redir((*current), (*tmp)))
            return (-1);
        (*tmp) = (*tmp)->next;
    }
    else if ((*tmp)->type == REDIR_APPEND)
    {
        if (for_append((*current), (*tmp)))
            return (-1);
        (*tmp) = (*tmp)->next;
    }
    return (0);
}