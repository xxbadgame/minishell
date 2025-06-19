/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:43:16 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/19 12:55:44 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

void	signal_and_pipe_redirect(t_cmd *cmd, int *in_fd, t_shell *shell,
		int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_choice_pipe(cmd, in_fd, pipefd);
	exec_choice(cmd, shell);
}

void	signal_and_single_redirect(t_cmd *cmd, t_shell *shell, int heredoc_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_choice_single(cmd, heredoc_fd);
	exec_choice(cmd, shell);
}

char	*cat_path(char **all_path, int i, char *cmd)
{
	char	*path;

	path = malloc(path_len(all_path[i], cmd));
	if (!path)
		return (free_tab(all_path), NULL);
	path[0] = '\0';
	ft_strncat(path, all_path[i], ft_strlen(all_path[i]) + 1);
	ft_strncat(path, "/", ft_strlen(all_path[i]) + 2);
	ft_strncat(path, cmd, path_len(all_path[i], cmd));
	return (path);
}
