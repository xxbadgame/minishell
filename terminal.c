/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:20:08 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/05/07 10:12:50 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

t_cmd **lexer_and_parsing(char *line)
{
	t_token **tokens;
	tokens = malloc(sizeof(t_token *)); 
	if(!tokens)
		return 0;
	*tokens = NULL;
	return(parsing_token(lexer(tokens,line)));
}

void exec(char *line, char **env)
{
	t_cmd *cmd;
	(void)env;
	
	cmd = *lexer_and_parsing(line);
	while(cmd != NULL)
	{
		exec_single_command(cmd, env);
		cmd = cmd->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
    (void)argv;
	t_env *env;
	char *line;

	t_cmd *cmd;
	
	cmd = malloc(sizeof(t_cmd *));
	env = init_env(envp);
	while (1)
	{
		line = readline("minishell> ");
        if (*line)
            add_history(line);
		exec(line, env->env_cpy);
		free(line);
	}
}