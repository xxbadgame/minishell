/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:libft/ft_strncmp.c
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
========
/*   get_next_line.h                                    :+:      :+:    :+:   */
>>>>>>>> execution:libft/get_next_line/get_next_line.h
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:libft/ft_strncmp.c
/*   Created: 2025/04/16 15:30:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/04/16 15:33:32 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	if (n == 0)
		return (0);
	n = n - 1;
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
========
/*   Created: 2025/04/30 06:54:20 by yannis            #+#    #+#             */
/*   Updated: 2025/04/30 08:31:25 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

char *get_next_line(int fd);

#endif
>>>>>>>> execution:libft/get_next_line/get_next_line.h
