/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/04/22 17:57:38 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

int get_path_command()
{
	char *path = getenv("PATH");
	if (path)
		printf("PATH = %s\n", path);
	else
		printf("PATH variable not found\n");
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

int main(char **envp) 
{
	char **cmd = {"ls", "-l", "-a", NULL}; 
	execute_command(cmd, envp);
}