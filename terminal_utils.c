/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:08:09 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/25 11:08:29 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	init_shell(t_shell *shell)
{
	shell->line = NULL;
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->last_exit = 0;
}
