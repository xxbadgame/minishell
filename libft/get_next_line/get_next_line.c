/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:52:29 by yannis            #+#    #+#             */
/*   Updated: 2025/06/19 13:59:54 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	find_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	build(int fd, char *buffer, char **result)
{
	ssize_t	bytes_read;
	char	*tmp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			buffer[0] = '\0';
			return (-1);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = *result;
		*result = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!*result)
			return (-1);
		if (find_n(buffer) != -1)
			break ;
	}
	return (0);
}

int	catch(char *buffer, char **result)
{
	int		end_line;
	char	*tmp_buffer;
	char	*tmp_result;

	end_line = find_n(*result);
	if (end_line != -1)
	{
		tmp_buffer = ft_substr(*result, end_line + 1, ft_strlen(*result)
				- end_line - 1);
		if (!tmp_buffer)
			return (-1);
		ft_strcpy(buffer, tmp_buffer);
		free(tmp_buffer);
		tmp_result = *result;
		*result = ft_substr(*result, 0, end_line + 1);
		free(tmp_result);
		if (!*result)
			return (-1);
	}
	else
		buffer[0] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	tmp = result;
	result = ft_strjoin(tmp, buffer);
	free(tmp);
	if (!result)
		return (NULL);
	if (build(fd, buffer, &result) == -1)
		return (free(result), NULL);
	if (result[0] == '\0')
		return (free(result), NULL);
	if (catch (buffer, &result) == -1)
		return (free(result), NULL);
	return (result);
}
