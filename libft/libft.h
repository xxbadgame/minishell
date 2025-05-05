/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:32:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/05 11:19:57 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"

int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *s);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*ft_strncat(char *dest, char *src, int n);
int		ft_strlcpy(char *dest, char *src, int size);

#endif