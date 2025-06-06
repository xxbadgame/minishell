/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:08 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/06 13:50:19 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	lexer_and_parsing(char *line, t_shell *shell)
{
	if (lexer(shell, line) == -1)
		return (free_tokens(shell), -1);

	if (parsing_token(shell) == -1)
		return (free_tokens(shell), free_cmds(shell), -1);
	return (0);
}

int	exec(char *line, t_shell *shell)
{
	t_cmd	*cmd;

	if (lexer_and_parsing(line, shell) == -1)
		return (-1);
	cmd = shell->cmds;
	if (cmd->next != NULL)
		pipeline(shell);
	else
	{
		if (exec_single_command(cmd, shell) == -1)
			return (free_tokens(shell), free_cmds(shell), -1);
	}
	return (0);
}

void	init_shell(t_shell *shell)
{
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->last_exit = 0;
}

int	loop_readline(t_shell *shell)
{
	char	*line;

	line = NULL;
	line = readline("minishell$ ");
	if (!line)
	{
		free_env(shell);
		free(shell);
		write(2, "exit\n", 5);
		exit(1);
	}
	if (*line != '\0')
	{
		add_history(line);
		exec(line, shell);
	}
	free_tokens(shell);
	free_cmds(shell);
	free(line);
	return (0);
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	
	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if(!shell)
		return (-1);
	shell->cmds = NULL;
	shell->tokens = NULL;
	argc = 0;
	init_shell(shell);
	shell->env = init_env(envp);
	if (!shell->env)
		return (perror("env failed"), -1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		loop_readline(shell);
	free_env(shell);
	free(shell);
	clear_history();
	return (0);
}
