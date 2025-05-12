/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:07:33 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/12 14:18:32 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_env(t_env *env)
{
	int i;

	i = 0;
	while(env->env_cpy[i])
		printf("%s\n",env->env_cpy[i++]);
	return (0);
}

// int main(int argc,char **argv,char **envp)
// {
// 	t_env *env;
// 	int i;
// 	i = 0;
// 	env = init_env(envp);
// 	builtin_env(env);

// }