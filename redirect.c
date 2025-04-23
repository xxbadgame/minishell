/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:18 by yannis            #+#    #+#             */
/*   Updated: 2025/04/23 13:56:58 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void redirect_right(const char *filename)
{
	int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        return 1;
    dup2(fd, 1);
    close(fd);
}

void redirect_left(const char *filename)
{
	int fd = open(filename, O_RDONLY, 0644);
    if (fd < 0)
        return 1;
    dup2(fd, 0);
    close(fd);
}

int main()
{
	int saved_stdout = dup(1);

	redirect_right("fichier.txt");

	printf("dans le fichier\n");

    dup2(saved_stdout, 1);
    close(saved_stdout);

    printf("dans le terminal\n");
}