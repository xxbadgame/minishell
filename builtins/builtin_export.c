/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:17:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/14 13:08:21 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int find_equal(t_cmd *cmd, char **new_env, int *i)
{
	if(ft_strchr(cmd->cmds[1], '=') == 1)
	{
		new_env[*i] = ft_strndup(cmd->cmds[1], ft_strlen(cmd->cmds[1]));
		if(!new_env)
			return(free_tab(new_env), -1);
	}
	else
	{
		new_env[*i] = ft_strjoin(cmd->cmds[1],"=");
		if(!new_env)
			return(free_tab(new_env), -1);
	}
	(*i)++;
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env *env)
{
	char **new_env;
	char **temp;
	int i;

	i = 0;
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy) + 2));
	if(!new_env)
		return(-1);
	add_in_env(env->env_cpy, new_env, &i);
	if(!new_env)
		return(free_tab(new_env), -1);
	find_equal(cmd, new_env, &i);
	new_env[i] = NULL;
	temp = env->env_cpy;
	env->env_cpy = new_env;
	return (free_tab(temp), 0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_cmd *cmd;
//     t_env *env;
//     env = init_env(envp);
// 	cmd->cmds = malloc(sizeof(char *) * 3);
// 	if (!cmd->cmds)
// 		return 1;
// 	cmd->cmds[0] = strdup("export");
// 	cmd->cmds[1] = strdup("NEW_VAR=value");
// 	cmd->cmds[2] = NULL;

//     if (builtin_export(cmd, env) == 0)
//     {
//         for (int i = 0; env->env_cpy[i]; i++)
//         {
//             printf("%s\n", env->env_cpy[i]);
//         }
//     }
//     else
//     {
//         printf("Error: Failed to export variable.\n");
//     }

//     return 0;
// }