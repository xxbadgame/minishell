#include "parsing.h"

void  add_cmd(t_cmd **cmds, t_cmd *new_cmd)
{
    t_cmd  *tmp;

    tmp = *cmds;
    if(*cmds == NULL)
        *cmds = new_cmd;
    else
    {
        while(tmp->next)
            tmp = tmp->next;
         tmp->next = new_cmd; 
    }
}
t_cmd *init_cmd()
{
    t_cmd *new_cmd;
    new_cmd = malloc(sizeof(t_cmd));
    if(!new_cmd)
        return NULL;
    new_cmd->argv = NULL;
    new_cmd->append = 0;
    new_cmd->infile = NULL;
    new_cmd->next = NULL;
    new_cmd->outfile = NULL;
    return (new_cmd);
}

t_cmd *parsing_token(t_token **tokens_list)
{
   t_cmd *cmds;
   char **args; 
   t_token *tmp;
   t_cmd *current;
   int argc; 
   cmds = NULL;
   current = init_cmd();
   tmp = *tokens_list;
   argc = 0;
   args = malloc(sizeof(char *) * 100);

   while(tmp)
   {
        if(tmp->type == WORD)
        {
            args[argc++] = ft_strdup(tmp->value);
            tmp = tmp->next;
        }
        else if(tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
        {
             for_redir(current,&tmp);
        }
        else    if(tmp->type == REDIR_APPEND)
        {
           for_append(current, &tmp);
        }
        else if(tmp->type == PIPE)
        {
            args[argc] = NULL;
            current->argv = args;
            add_cmd(&cmds,current);

            current = init_cmd();
            args = malloc(sizeof(char *) * 100);
            argc = 0;
            tmp = tmp->next;
        }
   }

   if(argc > 0)
   {
    args[argc] = NULL;
    current->argv = args;
    add_cmd(&cmds, current);
   }
   return (cmds);
}

int main()
{
    t_token **tokens;
    t_cmd *cmds;
   tokens = malloc(sizeof(t_token *));
   tokens = lexer(tokens,"echo salut | grep > ok ");
    cmds = parsing_token(tokens);
    int i = 0;
    while (cmds)
    {
        printf("Commande %d\n", i++);
        if (cmds->argv)
        {
            for (int j = 0; cmds->argv[j]; j++)
                printf("Arg[%d]: %s\n", j, cmds->argv[j]);
        }

        if (cmds->infile)
            printf("Infile: %s\n", cmds->infile);
        else
            printf("Infile: (none)\n");

        if (cmds->outfile)
            printf("Outfile: %s\n", cmds->outfile);
        else
            printf("Outfile: (none)\n");

        printf("Append: %d\n", cmds->append);
        printf("\n");

        cmds = cmds->next;
    }
}


