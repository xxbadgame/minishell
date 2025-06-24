/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:08 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/24 15:22:10 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	lexer_and_parsing(t_shell *shell)
{
	if (lexer(shell) == -1)
		return (free_tokens(shell), -1);
	if (parsing_token(shell) == -1)
		return (free(shell->line), free_tokens(shell), free_cmds(shell), -1);
	return (0);
}

int	exec_no_pipelines(t_cmd *cmd, t_shell *shell)
{
	if (cmd->cmd_args[0] == NULL && has_redirection(cmd))
	{
		if (cmd->heredoc == 1)
		{
			cmd->heredoc_fd = heredoc(cmd->infile, shell);
			if (cmd->heredoc_fd == -1)
				return (-1);
		}
		else
		{
			if (handle_redirection_only(cmd, shell) == -1)
				return (-1);
		}
		return (0);
	}
	if (exec_single_command(cmd, shell) == -1)
		return (free_tokens(shell), free_cmds(shell), -1);
	return (0);
}

int	exec(t_shell *shell)
{
	t_cmd	*cmd;

	if (lexer_and_parsing(shell) == -1)
		return (-1);
	cmd = shell->cmds;
	if (cmd->next != NULL)
	{
		if (pipeline(shell) == -1)
			return (-1);
	}
	else
	{
		if (exec_no_pipelines(cmd, shell) == -1)
			return (-1);
	}
	return (0);
}

void	init_shell(t_shell *shell)
{
	shell->line = NULL;
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->last_exit = 0;
}

int	loop_readline(t_shell *shell)
{
	shell->line = readline("minishell$ ");
	if (!shell->line)
	{
		free_env(shell);
		free(shell);
		write(2, "exit\n", 5);
		exit(0);
	}
	if ((*shell->line) != '\0')
	{
		add_history(shell->line);
		if (exec(shell) == -1)
		{
			free_tokens(shell);
			free_cmds(shell);
			free(shell->line);
			return (-1);
		}
	}
	free_tokens(shell);
	free_cmds(shell);
	free(shell->line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
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
	{
		if (loop_readline(shell) == -1)
			return (free_env(shell), free(shell), clear_history(), -1);
	}
	free_env(shell);
	free(shell);
	clear_history();
	return (0);
}
