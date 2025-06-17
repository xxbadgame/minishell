/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:39 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/17 10:14:35 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
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
	char			**cmd_args;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	int				heredoc_fd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_index_lexer
{
	int i;
	int j;
}	t_index_lexer;

typedef struct s_shell
{
	char			*line;
	t_env			*env;
	t_token			*tokens;
	t_cmd			*cmds;
	int				last_exit;
}					t_shell;

// builtins
int					builtin_cd(t_cmd *cmd, t_env *env);
int					builtin_echo(t_cmd *cmd);
int					builtin_export(t_cmd *cmd, t_env *env);
int					builtin_exit(t_shell *t_shell);
int					builtin_pwd(void);
int					builtin_unset(t_cmd *cmd, t_env *env);
int					exec_builtin(t_cmd *cmd, t_shell *shell);
int					is_builtin(t_cmd *cmd);
int					is_child_builtin(t_cmd *cmd);
int					builtin_export_env(t_env *env);
int					builtin_env(t_env *env, t_cmd *cmd);
int					find_var_env(t_cmd *cmd, char **env, int *j);

// env
t_env				*init_env(char **envp);
char				**create_path(char **env_cpy);
void				ft_get_path(t_env *env);
int					add_in_env(char **origin_env, char **dest_env, int *i);
char				*clean_str(char *str);

// exec
void				handle_next_pipe(int *in_fd, t_cmd *cmd, int *pipefd,
						int heredoc_fd);
int					launch_execve(t_cmd *cmd, t_shell *shell);
int					pipeline(t_shell *shell);
int					exec_single_command(t_cmd *cmd, t_shell *shell);
void				exec_choice(t_cmd *cmd, t_shell *shell);
int					redirect_right(char *filename);
int					double_redirect_right(char *filename);
int					redirect_left(char *filename);
int					heredoc(char *stop_word, t_shell *shell);
int					has_redirection(t_cmd *cmd);
int					handle_redirection_only(t_cmd *cmd, t_shell *shell);

// lexer
int					env_var_checker(char *str);
void				cut_quote(char *str, t_index_lexer *index,char **result,
						t_shell *t_shell);
int					check_quote(char *str);
int					find_quote(char *str, int *i, int *fisrt_quote,
						int *last_quote);
char				*loop_with_quote(char *str, int *i);
char				*loop_without_quote(char *str, int *i);
int					lexer(t_shell *shell);
t_token				*create_token(char *str, t_token_type type);
void				add_token(t_token **tokens_list, t_token *new_token);
int					ft_read_word(t_token **tokens_list, char *str, t_index_lexer *index,
						t_shell *shell);
int					ft_pipe(t_token **tokens_list, int *i);
int					ft_redir(char *str, t_token **tokens_list, int *i);
int					ft_heredoc_or_append(char *str, t_token **tokens_list,
						int *i);

// parsing
char				*find_str_in_env(t_env *env, char *str);
int					for_redir(t_cmd *current, t_token *tokens_list);
int					for_append(t_cmd *current, t_token *tokens_list);
int					for_heredoc(t_cmd *current_cmd, t_token *current_token);
int					for_pipe(t_cmd *current, t_token *tokens_list);
int					command_checker(int *i, t_token **current_token,
						t_cmd **current);
t_cmd				*create_cmd(int count_elem);
int					count_elem_cmd(t_token *current);
int					parsing_token(t_shell *shell);

// signal
void				handle_sigint(int sig);
void				handle_sig_output(int *flag_stop, int status);

// free
void				free_cmds(t_shell *shell);
void				free_tokens(t_shell *shell);
void				free_env(t_shell *shell);

#endif