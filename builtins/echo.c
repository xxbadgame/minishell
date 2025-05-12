/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:57:37 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/12 09:58:08 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd->argv[1], "-n", 2) == 0 && i++)
	{
		while (cmd->argv[i])
		{
			if (i > 2)
				printf(" %s", cmd->argv[i++]);
			else
				printf("%s", cmd->argv[i++]);
		}
	}
	else
	{
		while (cmd->argv[i])
		{
			if (i > 1)
				printf(" %s", cmd->argv[i++]);
			else
				printf("%s", cmd->argv[i++]);
		}
		printf("\n");
	}
	return (0);
}
