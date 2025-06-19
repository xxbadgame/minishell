/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:18 by yannis            #+#    #+#             */
/*   Updated: 2025/06/19 11:03:33 by engiusep         ###   ########.fr       */
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

int	expand_heredoc(char **line, char **new_line,t_shell *shell,int *i)
{
	char *var_name;
	int var_len;
	char *var_value;
	char *temp;
	
	var_len = env_var_checker((*line) + *i);
	var_name = ft_substr((*line), *i, var_len);
	if(!var_name)
		return (-1);
	var_value = find_str_in_env(shell->env, var_name);
	if(!var_value)
		return (free(var_name),-1);
	free(var_name);
	if (var_value)
	{
		temp = *new_line;
		*new_line = ft_strjoin(temp, var_value);
		free(temp);
		if(!(*new_line))
			return(free(var_value),-1);
	}
	free(var_value);
	*i += var_len;
	return (0);
}
int expand_last_exit(char **new_line,t_shell *shell,int *i)
{
	char *tmp;
	
	tmp = ft_itoa(shell->last_exit);
	if(!tmp)
		return(-1);
	*new_line = ft_strjoin((*new_line), tmp);
	if(!(*new_line))
		return(free(tmp),-1);
	free(tmp);
	*i += 2;
	return (0);
}
int	end_loop_heredoc(char **new_line,char **line,int *i)
{
	char *tmp;
	
	tmp = *new_line;
	*new_line = ft_joinchar(tmp, (*line)[*i]);
	free(tmp);
	if(!new_line)
		return(-1);
	(*i)++;
	return (0);
}
int loop_line_checker(char **line,t_shell *shell,char **new_line,int *i)
{
	if ((*line)[*i] == '$' && (*line)[*i + 1] == '?')
	{
		if(expand_last_exit(new_line,shell,i) == -1)
			return (-1);
	}
	else if ((*line)[*i] == '$' && env_var_checker((*line) + *i))
	{
		if(expand_heredoc(line,new_line,shell,i) == -1)
			return (-1);
	}
	else
	{
		if(end_loop_heredoc(new_line, line, i) == -1)
			return (-1);
	}
	return (0);
}
int 	line_checker(char **line, t_shell *shell)
{
	int i;
	char *new_line;
	
	
	i = 0;
	new_line = malloc(1);
	if (!new_line)
		return (-1);
	new_line[0] = '\0';
	while ((*line)[i])
	{
		if(loop_line_checker(line,shell,&new_line,&i) == -1)
			return (-1);
	}
	free(*line);
	*line = new_line;
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
		if(line_checker(&line, shell) == -1)
			return (free(line),-1);
		if (is_stop_word(line, stop_word))
			break;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
