#ifndef PARSING_H
# define PARSING_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../libft/libft.h"
#include "../d_lexer/lexer.h"


typedef struct s_cmd
{
    char **argv;
    char *infile;
    char *outfile;
    int append;
    struct s_cmd *next;

}   t_cmd;

char *ft_strdup(const char *s);
t_token **lexer(t_token **tokens_list, char *str);
int  for_redir(t_cmd *current, t_token *tmp);
void    for_append(t_cmd *current, t_token *tmp);
void    for_pipe(t_cmd *current, t_token **tmp);
void	command_checker(int *argc, t_token **tmp, t_cmd **current);
t_cmd *init_cmd(int count_elem);
int count_elem_cmd(t_token *current);


# endif