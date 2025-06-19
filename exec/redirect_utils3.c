/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:43:32 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/19 14:51:10 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	is_stop_word(char *line, char *stop_word)
{
	if (ft_strncmp(line, stop_word, ft_strlen(stop_word)) == 0
		&& ft_strlen(stop_word) == ft_strlen(line))
		return (1);
	return (0);
}

char	*str_trim_nl(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	check_var_value(char *var_value, char **new_line)
{
	char	*temp;

	if (var_value)
	{
		temp = *new_line;
		*new_line = ft_strjoin(temp, var_value);
		free(temp);
		if (!(*new_line))
			return (free(var_value), -1);
	}
	else
	{
		temp = *new_line;
		*new_line = ft_strndup("", 1);
		free(temp);
		if (!(*new_line))
			return (free(var_value), -1);
	}
	return (0);
}

int	expand_heredoc(char **line, char **new_line, t_shell *shell, int *i)
{
	char	*var_name;
	int		var_len;
	char	*var_value;

	var_len = env_var_checker((*line) + *i);
	var_name = ft_substr((*line), *i, var_len);
	if (!var_name)
		return (-1);
	var_value = find_str_in_env(shell->env, var_name);
	free(var_name);
	if (check_var_value(var_value, new_line) == -1)
		return (-1);
	*i += var_len;
	return (free(var_value), 0);
}
