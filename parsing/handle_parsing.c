/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:37:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/20 15:10:02 by engiusep         ###   ########.fr       */
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

char *find_str_in_env(t_env *env, char *str)
{
    int i;
    char **spl_var;
    char *result;

    i = 0;
    str++;
    while (env->env_cpy[i])
    {
        spl_var = ft_split(env->env_cpy[i], '=');
        if (ft_strncmp(spl_var[0], str, ft_strlen(spl_var[0])) == 0
            && ft_strlen(spl_var[0]) == ft_strlen(str))
        {
            result = ft_strndup(spl_var[1], ft_strlen(spl_var[1]));
            free_tab(spl_var);
            return(result);
        }
        i++;
        free_tab(spl_var);
    }
    return (NULL);
}

int checker_dollar(char *str)
{
    if (str[0] == '$')
    {
        return(1);
    }
    return (0);
}

int handle_word(int *i, t_token *tokens_list, t_cmd **current, t_env *env)
{
    int dollar;

    dollar = checker_dollar(tokens_list->value);
    if (dollar == 1)
    {
        (*current)->cmds[(*i)] = find_str_in_env(env, tokens_list->value);
        if ((*current)->cmds[(*i)] == NULL)
            printf("\n");
        (*i)++;
        return(0);
    }
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