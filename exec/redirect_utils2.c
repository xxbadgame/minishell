/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:53:35 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/19 14:44:30 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	expand_last_exit(char **new_line, t_shell *shell, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(shell->last_exit);
	if (!tmp)
		return (-1);
	tmp2 = *new_line;
	*new_line = ft_strjoin(tmp2, tmp);
	free(tmp2);
	free(tmp);
	if (!(*new_line))
		return (-1);
	*i += 2;
	return (0);
}

int	end_loop_heredoc(char **new_line, char **line, int *i)
{
	char	*tmp;

	tmp = *new_line;
	*new_line = ft_joinchar(tmp, (*line)[*i]);
	free(tmp);
	if (!new_line)
		return (-1);
	(*i)++;
	return (0);
}

int	loop_line_checker(char **line, t_shell *shell, char **new_line, int *i)
{
	if ((*line)[*i] == '$' && (*line)[*i + 1] == '?')
	{
		if (expand_last_exit(new_line, shell, i) == -1)
			return (-1);
	}
	else if ((*line)[*i] == '$' && env_var_checker((*line) + *i))
	{
		if (expand_heredoc(line, new_line, shell, i) == -1)
			return (-1);
	}
	else
	{
		if (end_loop_heredoc(new_line, line, i) == -1)
			return (-1);
	}
	return (0);
}

int	line_checker(char **line, t_shell *shell)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = malloc(1);
	if (!new_line)
		return (-1);
	new_line[0] = '\0';
	while ((*line)[i])
	{
		if (loop_line_checker(line, shell, &new_line, &i) == -1)
			return (-1);
	}
	free(*line);
	*line = new_line;
	return (0);
}
