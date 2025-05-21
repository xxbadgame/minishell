/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:13:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/21 13:23:04 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int command_pipeline_basic(t_cmd *cmd, int in_fd, int *pipefd, t_shell *shell)
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
    launch_execve(cmd, shell->env);
    return(0);
}

int command_pipeline_builtins(t_cmd *cmd, int in_fd, int *pipefd,t_shell *shell)
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
    if(exec_builtin(cmd,shell) == -1)
        return(-1);
    return(0);
}

int pipeline(t_shell *shell)
{
    int pipefd[2];
    int in_fd = 0;
    int pid;
    t_cmd *cmd;
    cmd = shell->cmds;

    while (cmd)
    {
        if(ft_strncmp(cmd->cmds[0], "exit", 4) == 0)
			builtin_exit(shell);
        if(ft_strncmp(cmd->cmds[0], "export", 6) == 0)
            cmd = cmd->next;
        if(ft_strncmp(cmd->cmds[0], "unset", 5) == 0)
            return(builtin_unset(cmd, shell->env), 0);
        if(ft_strncmp(cmd->cmds[0],"cd", 2) == 0)
            builtin_cd(cmd,shell->env);
        if (cmd->next)
            pipe(pipefd); 
        pid = fork();
        if (pid == 0)
        {
            if (is_builtin(cmd) == 0)
                command_pipeline_basic(cmd, in_fd, pipefd,shell);
            else
                command_pipeline_builtins(cmd, in_fd, pipefd,shell);
        }
        if (in_fd != 0)
            close(in_fd);
        if (cmd->next) 
        {
            close(pipefd[1]);
            in_fd = pipefd[0];
        }
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
    if (cmd->outfile != NULL && cmd->append == 0)
    {
        if(redirect_right(cmd->outfile))
            perror("redirect : ");
    }
    else if (cmd->outfile != NULL && cmd->append == 1)
        double_redirect_right(cmd->outfile);
    return 0;
}
