/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:13:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/07 10:09:33 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

/*
int wait_all_process()
{
    
}
*/

int command_pipeline(t_cmd *cmd, int in_fd, int *pipefd, char **envp)
{
    if(cmd->infile)
        in_fd = open(cmd->infile, O_RDONLY);
    if (in_fd != 0) {
        dup2(in_fd, 0);
        close(in_fd);
    }
    if (cmd->next) {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
    }
    launch_execve(cmd, envp);
    return(0);
}

int pipeline(t_cmd **cmds, char **envp)
{
    int pipefd[2];
    int in_fd = 0;
    t_cmd *cmd = *cmds;
    int pid;

    while (cmd)
    {
        if (cmd->next)
            pipe(pipefd);
        pid = fork();
        if (pid == 0)
            command_pipeline(cmd, in_fd, pipefd, envp);
        if (in_fd != 0)
            close(in_fd);
        if (cmd->next) {
            close(pipefd[1]);
            in_fd = pipefd[0];
        }
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
    return 0;
}
/*
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
	t_cmd cmd1, cmd2;

	// Commande 1 : cat exec.h
	char *args1[] = {"cat", "libft/ft_strjoin.c", NULL};
	cmd1.argv = args1;
	cmd1.infile = NULL;
	cmd1.outfile = NULL;
	cmd1.append = 0;
	cmd1.next = &cmd2;

	// Commande 2 : grep int
	char *args2[] = {"grep", "int", NULL};
	cmd2.argv = args2;
	cmd2.infile = NULL;
	cmd2.outfile = NULL;
	cmd2.append = 0;
	cmd2.next = NULL;

	t_cmd *cmds = &cmd1;
	pipeline(&cmds, envp);

	return 0;
}
*/