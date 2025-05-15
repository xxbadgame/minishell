/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:20:44 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/15 09:15:55 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int builtin_exit(t_shell *shell)
{
	free_tokens(shell);
	free_cmds(shell);
	free_env(shell);
	free(shell);
	exit(EXIT_SUCCESS);
}