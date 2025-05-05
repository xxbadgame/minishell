#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

char				*ft_strndup(char *str, int size);
t_token				*create_token(char *str, t_token_type type);
void				add_token(t_token **tokens_list, t_token *new_token);
void				ft_read_word(t_token **tokens_list, char *str, int *i);
void				ft_pipe(t_token **tokens_list, int *i);
void				ft_redir(char *str, t_token **tokens_list, int *i);
void				ft_heredoc_or_append(char *str, t_token **tokens_list,
						int *i);

#endif