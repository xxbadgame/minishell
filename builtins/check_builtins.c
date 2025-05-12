/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:06:45 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/12 09:59:42 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int is_builtins(t_cmd *cmd)
{
	if(ft_strncmp(cmd,"echo",4))
		echo(cmd);
	if(ft_strncmp(cmd,"cd",2))
		cd(cmd);
}