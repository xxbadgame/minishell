/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:39 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/28 11:08:19 by yannis           ###   ########.fr       */
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

extern volatile sig_atomic_t g_sigint;

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
	int				pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_index_lexer
{
	int				i;
	int				j;
	int				flag_symbole;
}					t_index_lexer;

typedef struct s_shell
{
	char			*line;
	t_env			*env;
	t_token			*tokens;
	t_cmd			*cmds;
	int				last_exit;
}					t_shell;

void				init_shell(t_shell *shell);
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
int					checker_var_format(t_cmd *cmd, int i);

// env
t_env				*init_env(char **envp);
int					add_in_env(char **origin_env, char **dest_env, int *i);
char				*clean_str(char *str);

// exec
void				loop_exec_pipeline(t_cmd **cmd, int *in_fd, int *pipefd);
int					no_child_pipe(t_cmd *cmd, t_shell *shell, int *pipefd,
						int *in_fd);
void				clean_and_exit(t_shell *shell, int status);
void				single_exit_checker(t_shell *shell);
void				check_end_exec(t_shell *shell, int heredoc_fd);
int					builtins_no_child(t_cmd *cmd, t_shell *shell);
void				handle_next_pipe(int *in_fd, t_cmd *cmd, int *pipefd);
int					launch_execve(t_cmd *cmd, t_shell *shell);
int					pipeline(t_shell *shell);
int					exec_single_command(t_cmd *cmd, t_shell *shell);
int					exec_choice(t_cmd *cmd, t_shell *shell);
int					redirect_right(char *filename);
int					double_redirect_right(char *filename);
int					redirect_left(char *filename);
int					heredoc(char *stop_word, t_shell *shell);
int					has_redirection(t_cmd *cmd);
int					handle_redirection_only(t_cmd *cmd);
char				*cat_path(char **all_path, int i, char *cmd);
int					path_len(char *path_env, char *cmd);
int					signal_and_single_redirect(t_cmd *cmd, t_shell *shell,
						int heredoc_fd);
int					redirect_choice_pipe_outfile(t_cmd *cmd, int *in_fd,
						int *pipefd);
int					redirect_choice_single(t_cmd *cmd, int heredoc_fd);
int					signal_and_pipe_redirect(t_cmd *cmd, int *in_fd,
						t_shell *shell, int *pipefd);
int					checker_redirection_only(t_cmd *cmd);
int					line_checker(char **line, t_shell *shell);
int					loop_line_checker(char **line, t_shell *shell,
						char **new_line, int *i);
int					end_loop_heredoc(char **new_line, char **line, int *i);
int					expand_last_exit(char **new_line, t_shell *shell, int *i);
int					expand_heredoc(char **line, char **new_line, t_shell *shell,
						int *i);
char				*str_trim_nl(char *line);
int					is_stop_word(char *line, char *stop_word);
int					pipe_loop(t_shell *shell, t_cmd *cmd, int *in_fd,
						int *pipefd);
int					check_all_arg_for_heredoc(t_cmd *cmd, t_shell *shell);
int					exec_pipeline(t_cmd *cmd, int *pipefd, t_shell *shell,
						int *in_fd);
void				close_fd_exit(int *pipefd, int in_fd);

// lexer
int					primary_check_quote(char *line, int *i);
int					handle_special_symbols(t_token **tokens_list, char *str,
						t_index_lexer *index);
int					primary_checker(char *line);
int					checker_flag_symbol(t_index_lexer *index, int flag_symbol,
						t_token *next, t_token *previous);
int					env_var_checker(char *str);
void				cut_quote(char *str, t_index_lexer *index, char **result,
						t_shell *t_shell);
int					check_quote(char *str);
int					lexer(t_shell *shell);
t_token				*create_token(char *str, t_token_type type);
void				add_token(t_token **tokens_list, t_token *new_token);
int					ft_read_word(t_token **tokens_list, char *str,
						t_index_lexer *index, t_shell *shell);
int					ft_pipe(t_token **tokens_list, t_index_lexer *index);
int					ft_redir(char *str, t_token **tokens_list, int *i);
int					ft_heredoc_or_append(char *str, t_token **tokens_list,
						int *i);
int					check_symbole_append_heredoc(char *str,
						t_index_lexer *index);
int					check_symbole_redirect(char *str, t_index_lexer *index);
int					checker_special_symbole(t_token *current);
int					check_char2(char *str, int i);
char				*malloc_var_in_env(char *str, t_shell *shell,
						t_index_lexer *index);
int					add_in_str(char **result, char *var_in_env,
						t_index_lexer *index);
int					dollar_var_env(char **result, t_index_lexer *index,
						char *str, t_shell *shell);
int					start_loop(char *str, t_index_lexer *index, char **result,
						t_shell *shell);
void				end_loop(char **result, char *str, t_index_lexer *index);
void				end_loop2(char **result, char *str, t_index_lexer *index);
void				after_dollar_checker(t_index_lexer *index, char **result,
						t_shell *shell);
int					env_var_checker(char *str);
int					check_quote(char *str);
int					in_quote(char *str, t_index_lexer *index, char **result,
						t_shell *shell);
// parsing
int					check_next(t_cmd *cmd, t_shell *shell);
int					inter_file(t_token **current_token, t_cmd **current_cmd,
						int direct_symbol_type);
char				*find_str_in_env(t_env *env, char *str);
int					for_redir(t_cmd *current, t_token *tokens_list);
int					for_append(t_cmd *current, t_token *tokens_list);
int					for_heredoc(t_cmd *current_cmd, t_token *current_token);
int					command_checker(int *i, t_token **current_token,
						t_cmd **current);
t_cmd				*create_cmd(int count_elem);
int					count_elem_cmd(t_token *current);
int					parsing_token(t_shell *shell);

// signal
void				handle_sigint(int sig);
void				handle_sig_output(int *flag_stop, int status);
void				setup_signals(struct sigaction *sa_new,
						struct sigaction *sa_old);

// free
void				free_cmds(t_shell *shell);
void				free_tokens(t_shell *shell);
void				free_env(t_shell *shell);

#endif