/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:18 by yannis            #+#    #+#             */
/*   Updated: 2025/06/19 12:43:54 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

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

int	heredoc(char *stop_word, t_shell *shell)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line = str_trim_nl(line);
		if (line_checker(&line, shell) == -1)
			return (free(line), -1);
		if (is_stop_word(line, stop_word))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
