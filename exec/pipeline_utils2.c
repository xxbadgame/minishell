/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:22:12 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/28 08:23:34 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

void	loop_exec_pipeline(t_cmd **cmd, int *in_fd, int *pipefd)
{
	handle_next_pipe(in_fd, *cmd, pipefd);
	*cmd = (*cmd)->next;
}
