#ifndef PARSING_H
# define PARSING_H

# include "../lexer/lexer.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;

}					t_cmd;

t_token				**lexer(t_token **tokens_list, char *str);
int					for_redir(t_cmd *current, t_token *tmp);
int				for_append(t_cmd *current, t_token *tmp);
int				for_pipe(t_cmd *current, t_token **tmp);
int				command_checker(int *argc, t_token **tmp, t_cmd **current);
t_cmd				*init_cmd(int count_elem);
int					count_elem_cmd(t_token *current);
t_cmd				**parsing_token(t_token **tokens_list);

#endif