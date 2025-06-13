/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:21:23 by yannis            #+#    #+#             */
/*   Updated: 2025/06/13 10:51:07 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void print_error(char *prefix, char *arg, char *suffix)
{
	if (prefix)
		ft_putstr_fd(prefix, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	if (suffix)
		ft_putstr_fd(suffix, 2);
}
