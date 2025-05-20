/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:17:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/20 10:00:37 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"




int count_add_var(t_cmd *cmd,t_env *env)
{
	int nb_var;
	int var_pos;
	int i;

	i = 1;
	var_pos = 0;
	nb_var = 0;
	
	while (cmd->cmds[nb_var])
		nb_var++;
	nb_var -= 1;
	while(cmd->cmds[i])
	{
		var_pos = find_var_env(cmd, env->env_cpy, &i);
		if (var_pos != -1)
			nb_var -= 1;
		i++;
	}
	return (nb_var);
	
}

int	replace_var_env(t_cmd *cmd, char **new_env, int var_pos ,int *j)
{
	char	*temp;

	if (ft_strchr(cmd->cmds[*j], '=') != 0)
	{
			temp = new_env[var_pos];
			new_env[var_pos] = clean_str(cmd->cmds[*j]);
			free(temp);
			if (!new_env[var_pos])
				return (-1);
	}
	return (0);
}

int	find_equal(t_cmd *cmd, char **new_env, int *i, int *j)
{
	new_env[*i] = clean_str(cmd->cmds[*j]);
	if (!new_env)
		return (free_tab(new_env), -1);
	(*i)++;
	return (0);
}
int	parse_cmd_arg(t_cmd *cmd,char **new_env, int *i)
{
	int j;
	int var_pos;

	j = 1;
	var_pos = 0;
	while(cmd->cmds[j])
	{
		var_pos = find_var_env(cmd, new_env, &j);
		if (var_pos == -1)
			find_equal(cmd, new_env, i, &j);
		else
			replace_var_env(cmd,new_env,var_pos,&j);
		j++;
	}
	return (0);
}
int	builtin_export(t_cmd *cmd, t_env *env)
{
	char	**new_env;
	char	**temp;
	int		i;
	int	nb_var;
	
	i = 0;
	nb_var = 0;
	if (!cmd->cmds[1])
		return (builtin_export_env(env), 0);
	nb_var = count_add_var(cmd,env);
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy) + 1 + nb_var));
	if (!new_env)
		return (-1);
	while(i < (tab_len(env->env_cpy) + 1 + nb_var))
		new_env[i++] = NULL;
	i = 0;
	add_in_env(env->env_cpy, new_env, &i);
	if (!new_env)
		return (free_tab(new_env), -1);
	parse_cmd_arg(cmd,new_env,&i);
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
// 		return (1);
// 	cmd->cmds[0] = strdup("export");
// 	cmd->cmds[1] = strdup("NEW_VAR=value");
// 	cmd->cmds[2] = NULL;

//     if (builtin_export(cmd, env) == 0)
//     {
//
//     }
//     else
//     {
//         printf("Error: Failed to export variable.\n");
//     }

//     return (0);
// }