/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:43:16 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/23 11:04:04 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	signal_and_pipe_redirect(t_cmd *cmd, int *in_fd, t_shell *shell,
		int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (redirect_choice_pipe_outfile(cmd, in_fd, pipefd) == -1)
		return (-1);
	if (exec_choice(cmd, shell) == -1)
		return (-1);
	return (0);
}

int	signal_and_single_redirect(t_cmd *cmd, t_shell *shell, int heredoc_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (redirect_choice_single(cmd, heredoc_fd) == -1)
		return (-1);
	if (exec_choice(cmd, shell) == -1)
		return (-1);
	return (0);
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

void check_end_exec(t_shell *shell, int heredoc_fd)
{
	if (heredoc_fd != -1)
		close(heredoc_fd);
	signal(SIGINT, SIG_IGN);
	single_exit_checker(shell);
	signal(SIGINT, handle_sigint);
}