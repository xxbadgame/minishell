/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:08:41 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/11 13:14:59 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinchar(char *s1, char c)
{
	int		len_s1;
	char	*joinchar;
	int		i;

	i = 0;
	len_s1 = ft_strlen(s1);
	joinchar = malloc(len_s1 + 2);
	if (!joinchar)
		return (NULL);
	while (s1[i])
	{
		joinchar[i] = s1[i];
		i++;
	}
	joinchar[i++] = c;
	joinchar[i] = '\0';
	return (joinchar);
}
