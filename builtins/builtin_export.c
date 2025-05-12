/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:17:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/12 14:15:13 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_export(t_cmd *cmd,t_env *env)
{
	char **new_env;
	char **temp;
	int i;

	i = 0;
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy) + 2));
	if(!new_env)
		return(-1);
	while(env->env_cpy[i])
	{
		new_env[i] = ft_strdup(env->env_cpy[i]);
		if(!new_env)
			return(free_tab(new_env), -1);
		i++;
	}
	if(ft_strchr(cmd->argv[1], '=') == 1)
	{
		new_env[i] = ft_strdup(cmd->argv[1]);
		if(!new_env)
			return(free_tab(new_env), -1);
	}
	else
	{
		new_env[i] = ft_strjoin(cmd->argv[1],"=");
		if(!new_env)
			return(free_tab(new_env), -1);
	}
	new_env[++i] = NULL;
	temp = env->env_cpy;
	env->env_cpy = new_env;
	free_tab(temp);
	return (0);
}

int main(int argc,char **argv,char **envp)
{
	t_env *env;
	t_cmd cmd;
	int i;
	i = 0;
	env = init_env(envp);
	cmd.argv = (char *[]){"export", "brimbrim patapim=salut", NULL};
	export(&cmd,env);
	while(env->env_cpy[i])
	{
		printf("%s\n",env->env_cpy[i++]);
	}

	free_tab(env->env_cpy);
	free(env);
}

