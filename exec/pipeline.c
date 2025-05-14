/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:13:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/14 13:46:02 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int command_pipeline(t_cmd *cmd, int in_fd, int *pipefd, t_env *env)
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
    launch_execve(cmd, env);
    return(0);
}

int pipeline(t_cmd *cmd, t_env *env)
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
            command_pipeline(cmd, in_fd, pipefd, env);
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
