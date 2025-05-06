/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:18 by yannis            #+#    #+#             */
/*   Updated: 2025/05/06 11:51:32 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int redirect_right(const char *filename)
{
	int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
		return (-1);
    if (dup2(fd, 1) == -1)
        return (-1);
    if(close(fd) == -1)
        return (-1);
	return(0);
}

int redirect_left(const char *filename)
{
	int fd = open(filename, O_RDONLY, 0644);
    if (fd < 0)
        return (-1);
    if(dup2(fd, 0) == -1)
        return(-1);
    if(close(fd) == -1)
        return(-1);
	return (0);
}

int double_redirect_right(const char *filename)
{
    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd < 0)
		return (-1);
    if (dup2(fd, 1) == -1)
        return (-1);
    if(close(fd) == -1)
        return (-1);
	return(0);
}

int heredoc(char *stop_word)
{
    int		pipefd[2];
    char	*line;

    if (pipe(pipefd) == -1)
        return (-1);

    while (1)
    {
        write(1, "heredoc> ", 9);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            return (-1);
        if (ft_strncmp(line, stop_word, ft_strlen(stop_word)) == 0
            && ft_strlen(stop_word) == (ft_strlen(line) - 1))
        {
            free(line);
            break ;
        }
        write(pipefd[1], line, ft_strlen(line));
        free(line);
    }
    close(pipefd[1]);
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    return (0);
}
/*
int main()
{
    // test 1
	int saved_stdout = dup(1);

	redirect_right("fichier.txt");

	write(1, "test 1\n", 7);

    dup2(saved_stdout, 1);
    close(saved_stdout);

    write(1, "test 2\n", 7);
   

    // test 2
    int saved_stdin = dup(0);

    heredoc("STOP");

    char *argv[] = {"cat", NULL};
    execvp("cat", argv);

    perror("execvp");
    dup2(saved_stdin, 0);
    close(saved_stdin);
    
}
*/