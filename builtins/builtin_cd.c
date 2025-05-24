/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:20:00 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 11:13:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int builtin_cd(t_cmd *cmd,t_env *env)
{
	char *cwd;
	char *new_path;
	char *temp;
	t_cmd *cmd_2;

	if (cmd->cmd_args[1][0] == '/')
	{
		if(chdir(cmd->cmd_args[1]) == -1)
			return(perror("dir"), -1);
		return (0);
	}
	cwd = getcwd(NULL,0);
	cmd_2 = malloc(sizeof(t_cmd));
	cmd_2->cmd_args = malloc(sizeof(char *) * 3);
	cmd_2->cmd_args[0] = ft_strndup("export",6);
	cmd_2->cmd_args[1] = ft_strjoin("OLDPWD=",cwd);
	cmd_2->cmd_args[2] = NULL;
	builtin_export(cmd_2,env);
	free(cmd_2->cmd_args[0]);
	free(cmd_2->cmd_args[1]);
	free(cmd_2);
	new_path = ft_strjoin(cwd,"/");
	if(!new_path)
		return(free(cwd), -1);
	temp = new_path;
	new_path = ft_strjoin(temp,cmd->cmd_args[1]);
	if(!new_path)
		return(free(temp), free(cwd), -1);
	free(temp);
	if(chdir(new_path) == -1)
		return(free(cwd),free(new_path),perror("dir"), -1);
	return(free(new_path),free(cwd),0);
}
