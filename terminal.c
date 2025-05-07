/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:08 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/07 15:39:10 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

t_cmd **lexer_and_parsing(char *line,t_shell **shell)
{
	(*shell)->tokens = malloc(sizeof(t_token *));
	if (!(*shell)->tokens)
		return (NULL);
	*((*shell)->tokens) = NULL;
	(*shell)->tokens = lexer(shell,line);
	if (!(*shell)->tokens)
		return (free((*shell)->tokens),NULL);
	(*shell)->cmds = parsing_token(shell);
	if (!(*shell)->cmds)
		return(free((*shell)->tokens),NULL);
	return((*shell)->cmds);
	return (NULL);
}

int exec(char *line,t_shell **shell)
{
	t_cmd *cmd;
	t_cmd **cmds;

	cmds = lexer_and_parsing(line,shell);
	if (!cmds)
		return (-1);
	cmd = *cmds;
	while(cmd != NULL)
	{
		if(exec_single_command(cmd, (*shell)->env->env_cpy) == -1)
			return(-1);
		cmd = cmd->next;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell *shell;
	char *line;
	int i;
	i = 0;

	shell = malloc(sizeof(t_shell));
	shell->cmds = NULL;
	shell->tokens = NULL;
	argc = 0;
	shell->env = init_env(envp);
	if(!shell->env)
		return(perror("env failed"),1);
	while (i < 5)
	{
		line = readline("minishell> ");
        if (*line)
		{
            add_history(line);
			exec(line,&shell);
		}
		free(line);
		i++;
	}
	free_env(&shell);
	free_cmds(&shell);
	free_tokens(&shell);
	free(shell);
	rl_clear_history();
	return 0;
}
