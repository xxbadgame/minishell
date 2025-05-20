/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:20:00 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/20 10:46:07 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int builtin_cd(t_cmd *cmd)
{
	char *cwd;
	char *new_path;
	char *temp;
	int i;

	i = 0;
	if (cmd->cmds[1][0] == '/')
	{
		if(chdir(cmd->cmds[1]) == -1)
			return(perror("dir"), -1);
		return (0);
	}
	cwd = getcwd(NULL,0);
	new_path = ft_strjoin(cwd,"/");
	if(!new_path)
		return(free(cwd), -1);
	temp = new_path;
	new_path = ft_strjoin(temp,cmd->cmds[1]);
	if(!new_path)
		return(free(temp), free(cwd), -1);
	free(temp);
	if(chdir(new_path) == -1)
		return(free(cwd),free(new_path),perror("dir"), -1);
	return(free(new_path),free(cwd),0);
}