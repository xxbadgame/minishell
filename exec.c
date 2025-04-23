/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/04/23 08:09:08 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

int get_path_command()
{
	char **all_path;
	//char *path;

	all_path = ft_split(getenv("PATH"), ':');
	int i = 0;
	while (all_path[i])
	{
		printf("chemin %d : %s\n", i, all_path[i]);
		i++;
	}
	

    return 0;
}

int	execute_command(char **cmd, char **envp)
{
	get_path_command();
	if (execve("/bin/ls", cmd, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int main() 
{
	//char **cmd = {"ls", "-l", "-a", NULL}; 
	//execute_command(cmd, envp);
	get_path_command();
}