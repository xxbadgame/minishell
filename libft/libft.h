/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:57:29 by yannis            #+#    #+#             */
/*   Updated: 2025/04/23 08:29:52 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);
char	*ft_strncat(char *dest, const char *src, size_t n);
size_t	ft_strlen(const char *str);