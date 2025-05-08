/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:40:57 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/08 13:38:43 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	for_redir(t_cmd *current, t_token *token)
{
    if (token->type == REDIR_IN && token->next && token->next->type == WORD)
    {
        current->infile = ft_strdup(token->next->value);
        if (!current->infile)
            return (-1);
    }
    else if (token->type == REDIR_OUT && token->next && token->next->type == WORD)
    {
        current->outfile = ft_strdup(token->next->value);
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

int	for_append(t_cmd *current, t_token *token)
{
    current->outfile = ft_strdup(token->value);
    if (!current->outfile)
        return (-1);
    current->append = 1;
    return (0);
}

int command_checker(int *argc, t_token **tokens_list, t_cmd **current)
{
    if ((*tokens_list)->type == WORD)
    {
        if (handle_word(argc, tokens_list, current))
            return (-1);
    }
    else if ((*tokens_list)->type == REDIR_IN || (*tokens_list)->type == REDIR_OUT || (*tokens_list)->type == REDIR_APPEND)
    {
        if (handle_redirection(current, tokens_list))
            return (-1);
    }
    else if ((*tokens_list)->type == PIPE || (*tokens_list)->next == NULL)
    {
        if (handle_pipe_or_end(argc, tokens_list, current))
            return (-1);
    }
    (*current)->argv[(*argc)] = NULL;
    *tokens_list = (*tokens_list)->next;
    return (0);
}
