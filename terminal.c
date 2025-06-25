/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:08 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/25 16:18:38 by engiusep         ###   ########.fr       */
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
			if (handle_redirection_only(cmd) == -1)
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
	int		pipe_run;

	pipe_run = 0;
	if (lexer_and_parsing(shell) == -1)
		return (-1);
	cmd = shell->cmds;
	if (cmd->next != NULL && cmd->next->cmd_args[0] != NULL)
	{
		pipe_run = pipeline(shell);
		if (pipe_run == -1)
			return (-1);
	}
	else
	{
		if (exec_no_pipelines(cmd, shell) == -1)
			return (-1);
		if (cmd->next != NULL && cmd->next->cmd_args[0] == NULL)
			checker_redirection_only(cmd->next);
	}
	return (0);
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
	shell->line = NULL;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		check_loop;

	check_loop = 0;
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
		check_loop = loop_readline(shell);
		if (check_loop == -1)
			return (free_env(shell), free(shell), clear_history(), -1);
	}
	return (free_env(shell), free(shell), clear_history(), 0);
}
