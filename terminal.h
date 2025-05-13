/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:39 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/13 09:28:35 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>


typedef struct s_env
{
	char			**env_cpy;
}					t_env;

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

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_shell
{
	t_env		*env;
    t_token		*tokens;
    t_cmd		*cmds;
}	t_shell;


// env
t_env		*init_env(char **envp);
char		**create_path(char **env_cpy);
void		ft_get_path(t_env *env);

// exec
int pipeline(t_cmd *cmds, char **envp);
int	launch_execve(t_cmd *cmd, char **envp);
int ft_listlen(t_cmd **cmds);
int exec_single_command(t_cmd *cmd, char **envp);

// lexer
int lexer(t_shell *shell, char *str);
t_token				*create_token(char *str, t_token_type type);
void				add_token(t_token **tokens_list, t_token *new_token);
int				ft_read_word(t_token **tokens_list, char *str, int *i);
int				ft_pipe(t_token **tokens_list, int *i);
int				ft_redir(char *str, t_token **tokens_list, int *i);
int				ft_heredoc_or_append(char *str, t_token **tokens_list,
						int *i);

// parsing
int					for_redir(t_cmd *current, t_token *tokens_list);
int					for_append(t_cmd *current, t_token *tokens_list);
int					for_pipe(t_cmd *current, t_token **tokens_list);
int					command_checker(int *argc, t_token **tokens_list, t_cmd **current);
t_cmd				*create_cmd(int count_elem);
int					count_elem_cmd(t_token *current);
int parsing_token(t_shell *shell);
int	handle_pipe_or_end(int *argc, t_token **token, t_cmd **current);
int handle_word(int *argc, t_token **token, t_cmd **current);
int handle_redirection(t_cmd **current, t_token **token);

//free
void free_cmds(t_shell *shell);
void free_tokens(t_shell *shell);
void free_env(t_shell *shell);

#endif