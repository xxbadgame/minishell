/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:08 by yannis            #+#    #+#             */
/*   Updated: 2025/04/22 16:20:46 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

/*
void execute(char **cmds)
{
    char	*pathname;
    int		pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (execve("/bin/ls", ))
	}
}
*/

int main() {
    char *argv[] = {"/bin/ls", "-l", NULL};
    char *envp[] = {NULL};

    if (execve("/bin/ls", argv, envp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    return 0;
}