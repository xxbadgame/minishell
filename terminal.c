/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:08 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/08 13:42:16 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int lexer_and_parsing(char *line, t_shell *shell)
{
	if (lexer(shell,line) == -1)
		return (free(shell->tokens),-1);
	if (parsing_token(shell) == -1)
		return(free(shell->tokens),-1);
	return (0);
}

int exec(char *line, t_shell *shell)
{
	t_cmd *cmd;

	if (lexer_and_parsing(line, shell) == -1)
		return(-1);
	cmd = shell->cmds;
	while(cmd != NULL)
	{
		if(exec_single_command(cmd, shell->env->env_cpy) == -1)
			return(-1);
		cmd = cmd->next;
	}
	return (0);
}

void init_shell(t_shell *shell)
{
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
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
	init_shell(shell);
	shell->env = init_env(envp);
	if(!shell->env)
		return(perror("env failed"),1);
	while (i < 5)
	{
		line = readline("minishell> ");
        if (*line)
		{
            add_history(line);
			exec(line,shell);
		}
		free(line);
		i++;
	}
	free_env(shell);
	free_cmds(shell);
	free_tokens(shell);
	free(shell);
	clear_history();             
	rl_clear_history();
    rl_clear_history();          
    rl_free_line_state();        
    rl_cleanup_after_signal();   
	return 0;
}
