/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:18 by yannis            #+#    #+#             */
/*   Updated: 2025/06/19 14:32:21 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

volatile int	g_heredoc_sigint = 0;

int	redirect_right(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (dup2(fd, 1) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	redirect_left(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
		return (-1);
	if (dup2(fd, 0) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	double_redirect_right(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	if (dup2(fd, 1) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	heredoc_loop(char **line, t_shell *shell, char *stop_word, int *pipefd)
{
	write(1, "heredoc> ", 9);
	*line = get_next_line(STDIN_FILENO);
	if (g_heredoc_sigint)
		return (2);
	if (!*line)
		return (2);
	*line = str_trim_nl(*line);
	line_checker(line, shell);
	if (is_stop_word(*line, stop_word))
		return (free(*line), 2);
	write(pipefd[1], *line, ft_strlen(*line));
	write(pipefd[1], "\n", 1);
	free(*line);
	return (0);
}

int	heredoc(char *stop_word, t_shell *shell)
{
	int					pipefd[2];
	char				*line;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	setup_signals(&sa_old, &sa_new);
	if (pipe(pipefd) == -1)
		return (-1);
	while (!g_heredoc_sigint)
	{
		if (heredoc_loop(&line, shell, stop_word, pipefd) == 2)
			break ;
	}
	close(pipefd[1]);
	sigaction(SIGINT, &sa_old, NULL);
	if (g_heredoc_sigint)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
