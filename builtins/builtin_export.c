/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:17:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/15 13:34:21 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int replace_var_env(t_cmd *cmd,t_env *env,int *i)
{
	char *temp;
	
	if (ft_strchr(cmd->cmds[1], '=') != 0)
	{
		temp = env->env_cpy[*i];
		env->env_cpy[*i] = ft_strndup(cmd->cmds[1],
				ft_strlen(cmd->cmds[1]));
		free(temp);
		if (!env->env_cpy[*i])
			return (-1);
	}
	else
	{
		temp = env->env_cpy[*i];
		env->env_cpy[*i] = ft_strjoin(cmd->cmds[1], "=");
		free(temp);
		if (!env->env_cpy[*i])
			return (-1);
	}
	return (0);
}
int	find_var_env(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*sub_cmd;
	char	*sub_env_var;
	int size_cmd;

	i = -1;
	while (env->env_cpy[++i])
	{
		size_cmd = ft_strchr(cmd->cmds[1], '=');
		if (size_cmd == 0)
			sub_cmd = ft_substr(cmd->cmds[1], 0, ft_strlen(cmd->cmds[1]));
		else
			sub_cmd = ft_substr(cmd->cmds[1], 0, size_cmd);
		sub_env_var = ft_substr(env->env_cpy[i], 0, ft_strchr(env->env_cpy[i], '='));
		if (ft_strncmp(sub_cmd, sub_env_var, ft_strlen(sub_env_var)) == 0
		&& ft_strlen(sub_cmd) == ft_strlen(sub_env_var))
		{
			if(replace_var_env(cmd,env,&i) == -1)
				return (free_tab(env->env_cpy),free(sub_cmd),free(sub_env_var),-1);
			return (1);
		}
		free(sub_cmd);
		free(sub_env_var);
	}
	return (0);
}

int	find_equal(t_cmd *cmd, char **new_env, int *i)
{
	if (ft_strchr(cmd->cmds[1], '=') != 0)
	{
		new_env[*i] = ft_strndup(cmd->cmds[1], ft_strlen(cmd->cmds[1]));
		if (!new_env)
			return (free_tab(new_env), -1);
	}
	else
	{
		new_env[*i] = ft_strjoin(cmd->cmds[1], "=");
		if (!new_env)
			return (free_tab(new_env), -1);
	}
	(*i)++;
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env *env)
{
	char	**new_env;
	char	**temp;
	int		i;

	i = 0;
	if(!cmd->cmds[1])
		return(builtin_export_env(env),0);
	if (find_var_env(cmd, env) == 1)
		return (0);
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy) + 2));
	if (!new_env)
		return (-1);
	add_in_env(env->env_cpy, new_env, &i);
	if (!new_env)
		return (free_tab(new_env), -1);
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