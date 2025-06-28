/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:05:29 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/28 08:55:20 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	inter_file(t_token **current_token, t_cmd **current_cmd,
		int direct_symbol_type)
{
	int	fd;

	if ((*current_token)->next && ((*current_token)->next->type == REDIR_OUT
			|| (*current_token)->next->type == REDIR_APPEND)
		&& direct_symbol_type == 1)
	{
		fd = open((*current_cmd)->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open outfile"), -1);
		close(fd);
		free((*current_cmd)->outfile);
	}
	if ((*current_token)->next && ((*current_token)->next->type == REDIR_IN
			|| (*current_token)->next->type == HEREDOC)
		&& direct_symbol_type == 2)
	{
		fd = open((*current_cmd)->infile, O_RDONLY, 0644);
		if (fd < 0)
			return (perror("open infile"), -1);
		close(fd);
		free((*current_cmd)->infile);
	}
	return (0);
}
