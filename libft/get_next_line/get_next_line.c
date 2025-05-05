/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:52:29 by yannis            #+#    #+#             */
/*   Updated: 2025/04/30 08:45:34 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
    int i;
    int j;
    int len1;
    int len2;
    char *result;

    i = 0;
    j = 0;
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    result = malloc(len1 + len2 + 1);
    if (!result)
        return(NULL);
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    while (s2[j])
        result[i++] = s2[j++];
    result[i] = '\0';
    return (result);
}

int find_n(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char *ft_substr(char *big, int start, int len)
{
    char *result;
    int i;

    result = malloc(len + 1);
    if (!result)
        return (NULL);
    i = 0;
    while (i < len && big[start + i])
    {
        result[i] = big[start + i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

void ft_strlcpy(char *dst, char *src, int len)
{
    int i;

    i = 0;
    while (src[i] && i < len)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

int build(int fd, char *buffer, char **result)
{
    ssize_t bytes_read;
    char *tmp;

    while (1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            buffer[0] = '\0';
            return(-1);
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        tmp = *result;
        *result = ft_strjoin(tmp, buffer);
        free(tmp);
        if (!*result)
            return(-1);
        if (find_n(buffer) != -1)
            break;
    }
    return(0);
}

int catch(char *buffer, char **result)
{
    int end_line;
    char *tmp_buffer;
    char *tmp_result;

    end_line = find_n(*result);
    if (end_line != -1)
    {
        tmp_buffer = ft_substr(*result, end_line + 1, ft_strlen(*result));
        if (!tmp_buffer)
            return(-1);
        ft_strlcpy(buffer, tmp_buffer, ft_strlen(tmp_buffer));
        free(tmp_buffer);
        tmp_result = *result;
        *result = ft_substr(*result, 0, end_line + 1);
        free(tmp_result);
        if (!*result)
            return(-1);
    }
    else
        buffer[0] = '\0';
    return (0);
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char *result;
    char *tmp;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    result = malloc(1);
    if (!result)
        return (NULL);
    result[0] = '\0';
    tmp = result;
    result = ft_strjoin(tmp, buffer);
    free(tmp);
    if (!result)
        return(NULL);
    if(build(fd, buffer, &result) == -1)
        return (free(result), NULL);
    if (result[0] == '\0')
        return(free(result), NULL);
    if (catch(buffer, &result) == -1)
        return (free(result), NULL);
    return (result);
}

/*
int main(int argc, char const *argv[])
{
    int fd = open("test.txt", O_RDONLY);

    char *str;
    char *str2;

    str = get_next_line(fd);
    printf("%s",str);
    free(str);
    str = get_next_line(fd);
    printf("%s",str);
    free(str);
    return 0;
}
*/

