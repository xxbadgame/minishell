/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:13:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/13 09:30:16 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

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

int pipeline(t_cmd *cmd, char **envp)
{
    int pipefd[2];
    int in_fd = 0;
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
