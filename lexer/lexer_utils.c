/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:57:09 by engiusep          #+#    #+#             */
/*   Updated: 2025/04/16 15:05:13 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


char *ft_strndup(char *str,int size)
{
	int i;
	char *new;
	
	i = 0;
	new = malloc(size * sizeof(char) + 1);
	while(i < size)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}