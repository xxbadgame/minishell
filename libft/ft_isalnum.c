/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:21:53 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/06/19 13:06:58 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int character)
{
	if ((character >= 'A' && character <= 'Z') || (character >= 'a'
			&& character <= 'z') || (character >= '0' && character <= '9'))
		return (1);
	return (0);
}
