/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:18 by yannis            #+#    #+#             */
/*   Updated: 2025/04/23 14:17:29 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int redirect_right(const char *filename)
{
	int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
		return (-1);
    dup2(fd, 1);
    close(fd);
	return(0);
}

int redirect_left(const char *filename)
{
	int fd = open(filename, O_RDONLY, 0644);
    if (fd < 0)
        return (-1);
    dup2(fd, 0);
    close(fd);
	return (0);
}

int main()
{
    // test 1
    /*
	int saved_stdout = dup(1);

	redirect_right("fichier.txt");

	write(1, "test 1\n", 7);

    dup2(saved_stdout, 1);
    close(saved_stdout);

    write(1, "test 2\n", 7);
    */

    // test 2
    /*
    int saved_stdin = dup(0);

    redirect_left("fichier.txt");

    char *argv[] = {"cat", NULL};
    execvp("cat", argv);

    perror("execvp");
    dup2(saved_stdin, 0);
    close(saved_stdin);
    */
}