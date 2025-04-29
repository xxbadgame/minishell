/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:39:28 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/04/29 13:46:40 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void complete_path(char **path_edit, char **cmds_path)
{
	int i;
	int j;
	
	i = 1;
	j = 0;
	while (cmds_path[j])
		path_edit[i++] = ft_strdup(cmds_path[j++]);
	path_edit[i] = NULL;
	return ;
}

char **create_path(char **env_cpy)
{
	char *path_origin;
	char **path_edit;
	char **cmds_path;
	int tab_len;
	(void)env_cpy;
	
	path_origin = getenv("PATH");
	cmds_path = ft_split(path_origin, ':');
	tab_len = ft_tablen(cmds_path);
	path_edit = malloc(tab_len * (sizeof(char *) + 2));
	path_edit[0] = ft_strdup("/usr/local/builtins");
	complete_path(path_edit, cmds_path);
	return (path_edit);
}

/*
int main(int argc, char **argv, char **envp)
{
	(void)argc;
    (void)argv;
	t_env *env = init_env(envp);
	
	env->path_edit = create_path(env->env_cpy);

	int i = 0;
	while (env->path_edit[i])
		printf("%s\n", env->path_edit[i++]);
}
*/