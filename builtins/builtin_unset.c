/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:19:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/12 14:15:04 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_unset(t_cmd *cmd,t_env *env)
{
	char **new_env;
	char **temp;
	int i;
	int j;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (tab_len(env->env_cpy)));
	if(!new_env)
		return(-1);
	while(env->env_cpy[i])
	{
		if(ft_strncmp(env->env_cpy[i],cmd->argv[1],ft_strlen(cmd->argv[1])) != 0)
		{
			new_env[j] = ft_strdup(env->env_cpy[i]);
			if(!new_env)
				return(free_tab(new_env), -1);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	temp = env->env_cpy;
	env->env_cpy = new_env;
	return (free_tab(temp), 0);
}
// int main(int argc,char **argv,char **envp)
// {
// 	t_env *env;
// 	t_cmd cmd;
// 	int i;
// 	i = 0;
// 	env = init_env(envp);
// 	cmd.argv = (char *[]){"unset", "salut", NULL};
// 	unset(&cmd,env);
// 	while(env->env_cpy[i])
// 	{
// 		printf("%s\n",env->env_cpy[i++]);
// 	}
// 	free_tab(env->env_cpy);
// 	free(env);
// }