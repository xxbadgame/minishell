/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:13:39 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/24 16:26:32 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int pipeline(t_shell *shell)
{
    int pipefd[2];
    int in_fd = 0;
    int pid;
    t_cmd *cmd;
    cmd = shell->cmds;

    while (cmd)
    {
        if(ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0)
			builtin_exit(shell);
        if(ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
            cmd = cmd->next;
        if(ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0)
            return(builtin_unset(cmd, shell->env), 0);
        if(ft_strncmp(cmd->cmd_args[0],"cd", 2) == 0)
            builtin_cd(cmd,shell->env);
        if (cmd->next)
            pipe(pipefd); 
        pid = fork();
        if (pid == 0)
        {
            if (cmd->infile != NULL && cmd->heredoc == 0)
			    redirect_left(cmd->infile);
            else if (cmd->infile != NULL && cmd->heredoc == 1)
                heredoc(cmd->infile);
            else if (in_fd != 0)
            {
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (cmd->outfile != NULL && cmd->append == 0)
                redirect_right(cmd->outfile);
            else if (cmd->outfile != NULL && cmd->append == 1)
                double_redirect_right(cmd->outfile);
            else if (cmd->next)
            {
                dup2(pipefd[1], 1);
                close(pipefd[1]);
                close(pipefd[0]);
            }
            if (is_builtin(cmd) == 0)
               launch_execve(cmd, shell->env);
            else
                exec_builtin(cmd, shell);
            exit(0);
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
    return 0;
}
