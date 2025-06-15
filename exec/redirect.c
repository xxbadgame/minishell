/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:18 by yannis            #+#    #+#             */
/*   Updated: 2025/06/15 07:15:49 by yannis           ###   ########.fr       */
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

static int	is_stop_word(char *line, char *stop_word)
{
	if (ft_strncmp(line, stop_word, ft_strlen(stop_word)) == 0
		&& ft_strlen(stop_word) == ft_strlen(line))
		return (free(line), 1);
	return (0);
}

char *str_trim_nl(char *line)
{
    size_t len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return line;
}

void line_checker(char **line, t_shell *shell)
{
	int i = 0;
	char *new_line = ft_strndup("", 1);
	char *var_value;
	char *tmp;
	int var_len;

	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			tmp = ft_itoa(shell->last_exit);
			new_line = ft_strjoin(new_line, tmp);
			free(tmp);
			i += 2;
		}
		else if ((*line)[i] == '$' && env_var_checker((*line) + i))
		{
			var_len = env_var_checker((*line) + i);
			char *var_name = ft_substr((*line), i, var_len);
			var_value = find_str_in_env(shell->env, var_name);
			free(var_name);
			if (var_value)
				new_line = ft_strjoin(new_line, var_value);
			i += var_len;
		}
		else
		{
			new_line = ft_joinchar(new_line, (*line)[i]);
			i++;
		}
	}
	free(*line);
	*line = new_line;
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
		line_checker(&line, shell);
		if (is_stop_word(line, stop_word))
			break;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
