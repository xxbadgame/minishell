/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 08:27:30 by yannis            #+#                #+#             */
/*   Updated: 2025/04/25 15:50:07 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
    if (i < BUFFER)
        return (i);
	return (-1);
}

void build(int fd, char *buffer, char **result)
{
    ssize_t bytes_read;
    char *tmp;
    int     end_line;

	while (1)
    {
        bytes_read = read(fd, buffer, BUFFER);
        if (bytes_read < 0)
        {
            free(*result);
            *result = NULL;
            return;
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        tmp = ft_strjoin(*result, buffer);
        free(*result);
        *result = tmp;
        end_line = find_n(buffer);
        if (end_line != -1)
            break;
    }
}

void catch(char **result, char *buffer)
{
    int end_line;
    char *tmp_result;
    char *tmp_buffer;

    end_line = find_n(*result);
    if (end_line != -1)
    {
        tmp_result = ft_substr(*result, 0, end_line + 1);
        tmp_buffer = ft_substr(*result, end_line + 1, ft_strlen(*result));
        ft_strlcpy(buffer, tmp_buffer, BUFFER + 1);
        free(tmp_buffer);
        free(*result);
        *result = tmp_result;
    } 
    else
        buffer[0] = '\0';
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER + 1];
    char *result;
    char *temp;

    if (fd < 0 || BUFFER <= 0)
        return (NULL);
    result = malloc(1);
    if (!result)
        return (NULL);
    result[0] = '\0';
    
    if (buffer[0] != '\0')
    {
        temp = ft_strjoin(result, buffer);
        free(result);
        if (!temp)
            return (NULL);
        result = temp;
    }
        
    build(fd, buffer, &result);
    
    // Si result est vide après build, rien à lire
    if (result && result[0] == '\0')
    {
        free(result);
        return (NULL);
    }
    
    catch(&result, buffer);
    
    return (result);
}

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
}