/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:37:14 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 11:40:59 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../terminal.h"

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
        return(1);
    return (0);
}

int	for_redir(t_cmd *current_cmd, t_token *current_token)
{
    if (current_token->type == REDIR_IN && current_token->next && current_token->next->type == WORD)
    {
        current_cmd->infile = ft_strndup(current_token->next->value, ft_strlen(current_token->next->value));
        if (!current_cmd->infile)
            return (-1);
        current_cmd->heredoc = 0;
    }
    else if (current_token->type == REDIR_OUT && current_token->next && current_token->next->type == WORD)
    {
        current_cmd->outfile = ft_strndup(current_token->next->value,ft_strlen(current_token->next->value));
        if (!current_cmd->outfile)
            return (-1);
        current_cmd->append = 0;
    }
    else
    {
        write(2, "ERROR\n", 6);
        return (-1);
    }
    return (0);
}

int	for_append(t_cmd *current_cmd, t_token *current_token)
{
    current_cmd->outfile = ft_strndup(current_token->next->value,ft_strlen(current_token->next->value));
    if (!current_cmd->outfile)
        return (-1);
    current_cmd->append = 1;
    return (0);
}

int	for_heredoc(t_cmd *current_cmd, t_token *current_token)
{
    current_cmd->infile = ft_strndup(current_token->next->value,ft_strlen(current_token->next->value));
    if (!current_cmd->infile)
        return (-1);
    current_cmd->heredoc = 1;
    return (0);
}

