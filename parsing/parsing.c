/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:50:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/14 12:10:29 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

t_cmd	*create_cmd(int count_elem)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmds = malloc(sizeof(char *) * (count_elem + 1));
	if (!new_cmd->cmds)
		return (free(new_cmd), NULL);
	new_cmd->append = 0;
	new_cmd->infile = NULL;
	new_cmd->next = NULL;
	new_cmd->outfile = NULL;
	return (new_cmd);
}

int	count_elem_cmd(t_token *current)
{
	t_token	*tmp;
	int		count_elem;

	tmp = current;
	count_elem = 0;
	while (tmp && tmp->type != PIPE)
	{
		count_elem++;
		tmp = tmp->next;
	}
	return (count_elem);
}

int	parsing_token(t_shell *shell)
{
	t_cmd	*current;
	t_token *current_token;
	int		i;

	i = 0;
	current = create_cmd(count_elem_cmd(shell->tokens));
	if(!current)
		return (-1);
	current_token = shell->tokens;
	shell->cmds = current; 
	while (current_token)
	{
		if(command_checker(&i, current_token, &current) == -1)
		  	return(free_cmds(shell),free(current),free_tab(current->cmds), -1);
		current_token = current_token->next;
	}
	return (0);
}



// // Fonction de test : crée un token et l'ajoute à la liste
// void add_test_token(t_token **list, char *value, t_token_type type)
// {
// 	t_token *token = create_token(ft_strndup(value,ft_strlen(value)), type);
// 	if (!token)
// 	{
// 		fprintf(stderr, "Erreur create_token\n");
// 		exit(1);
// 	}
// 	add_token(list, token);
// }

// // Affiche les commandes après parsing
// void print_cmds(t_shell *shell)
// {
// 	t_cmd *cmd = shell->cmds;

// 	while (cmd)
// 	{
// 		printf("📦 Commande:\n");
// 		for (int i = 0; cmd->cmds[i]; i++)
// 			printf("  🔹 Arg[%d]: %s\n", i, cmd->cmds[i]);
// 		if (cmd->infile)
// 			printf("  📥 infile: %s\n", cmd->infile);
// 		if (cmd->outfile)
// 			printf("  📤 outfile: %s\n", cmd->outfile);
// 		cmd = cmd->next;
// 	}
// }

// int main(void)
// {
// 	t_shell shell;
// 	shell.tokens = NULL;
// 	shell.cmds = NULL;
// 	shell.env = NULL;

// 	// 🧪 Simulation manuelle d'une ligne : echo hello | grep h
// 	add_test_token(&shell.tokens, "echo", WORD);
// 	add_test_token(&shell.tokens, "hello", WORD);
// 	add_test_token(&shell.tokens, "|", PIPE);
// 	add_test_token(&shell.tokens, "grep", WORD);
// 	add_test_token(&shell.tokens, "h", WORD);

// 	if (parsing_token(&shell) == -1)
// 	{
// 		fprintf(stderr, "Erreur de parsing\n");
// 		return (1);
// 	}

// 	print_cmds(&shell);

// 	// Nettoyage mémoire
// 	free_cmds(&shell);
// 	free_tokens(&shell);

// 	return 0;
// }

