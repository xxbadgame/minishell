/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/04/23 12:28:48 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

int	path_len(char *path_env, char *cmd)
{
	int	len_path_env;
    int	len_cmd;
	int	size_path;

	len_path_env = ft_strlen(path_env);
	len_cmd = ft_strlen(cmd);
	size_path = len_path_env + 1 + len_cmd + 1;
	return (size_path);
}

char *get_path_command(char *cmd)
{
	char **all_path;
	char *path;
	int i;

	i = 0;
	all_path = ft_split(getenv("PATH"), ':');
	while (all_path[i])
	{
		path = malloc(path_len(all_path[i], cmd));
		if (!path)
    		return (free_split(all_path), NULL);
		path[0] = '\0';
		ft_strncat(path, all_path[i], ft_strlen(all_path[i]) + 1);
		ft_strncat(path, "/", ft_strlen(all_path[i]) + 2);
		ft_strncat(path, cmd, path_len(all_path[i], cmd));
		if (access(path, X_OK) == 0)
			return(free_split(all_path), path);
		free(path);
		i++;
	}
	free_split(all_path);
    return NULL;
}

int	execute_command(char **cmd, char **envp)
{
	char *path = get_path_command(cmd[0]);
	int pid;

	pid = fork();
	if (pid < 0)
		perror("pid");
	else if (pid == 0)
	{
		if (execve(path, cmd, envp) == -1)
		{
			perror("execve");
			free(path);
			return (-1);
		}
	}
	free(path);
	return (0);
}

int main(int argc, char **argv, char **envp) 
{
	(void)argv;
	(void)argc;
	(void)envp;
	
	char *cmd[] = {"ls", "-l", "-a", NULL}; 
	execute_command(cmd, envp);
	
	return (0);
}