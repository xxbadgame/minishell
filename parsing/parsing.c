/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:50:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/04/24 14:51:16 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *init_cmd(int count_elem)
{
    t_cmd *new_cmd;
    new_cmd = malloc(sizeof(t_cmd));
    if(!new_cmd)
        return NULL;
    new_cmd->argv = malloc(sizeof(char *) * (count_elem + 1));
    if (!new_cmd->argv)
        return (free(new_cmd), NULL);
    new_cmd->append = 0;
    new_cmd->infile = NULL;
    new_cmd->next = NULL;
    new_cmd->outfile = NULL;
    return (new_cmd);
}

int count_elem_cmd(t_token *current)
{
    t_token *tmp;
    int count_elem;
    

    tmp = current;
    count_elem = 0;
    while (tmp && tmp->type != PIPE)
    {
        count_elem++;
        tmp = tmp->next;
    }
    return (count_elem);
}

t_cmd **parsing_token(t_token **tokens_list)
{
   t_cmd **cmds;
   t_token *tmp;
   t_cmd *current;
   int argc;
   
   argc = 0;
   tmp = *tokens_list;
   current = init_cmd(count_elem_cmd(tmp));
   cmds = malloc(sizeof(t_cmd *));
    *cmds = current;
   while(tmp)
   {
        command_checker(&argc, &tmp, &current);
        tmp = tmp->next;
    }
   return (cmds);
}

int main()
{
    t_token **tokens;
    t_cmd **cmds;
    t_cmd *current_cmd;
    int i;

    tokens = malloc(sizeof(t_token *));
    if (!tokens)
    {
        perror("Malloc failed for tokens");
        return (1);
    }

    tokens = lexer(tokens, "cat echo | salut | fichier.txt hf");
    if (!tokens)
    {
        fprintf(stderr, "Lexer failed\n");
        free(tokens);
        return (1);
    }

    cmds = parsing_token(tokens);
    if (!cmds)
    {
        fprintf(stderr, "Parsing failed\n");
        free(tokens);
        return (1);
    }

    i = 0;
    current_cmd = *cmds;
    while (current_cmd)
    {
        printf("Commande %d\n", i++);
        if (current_cmd->argv)
        {
            for (int j = 0; current_cmd->argv[j]; j++)
                printf("Arg[%d]: %s\n", j, current_cmd->argv[j]);
        }

        if (current_cmd->infile)
            printf("Infile: %s\n", current_cmd->infile);
        else
            printf("Infile: (none)\n");

        if (current_cmd->outfile)
            printf("Outfile: %s\n", current_cmd->outfile);
        else
            printf("Outfile: (none)\n");

        printf("Append: %d\n", current_cmd->append);
        printf("\n");

        current_cmd = current_cmd->next;
    }

    // Libération de la mémoire
   // free(tokens);
   // free_cmds(cmds); // Implémentez une fonction pour libérer cmds et ses éléments
    return (0);
}
