#include <stdlib.h>

int ft_strlen(const char *s)
{
    int i;
    i = 0;
    while(s[i])
        i++;
    return (i);
}

char *ft_strdup(const char *s)
{
    int size;
    char *ptr;
    int i;
    i = 0;
    size = ft_strlen(s);
    ptr = malloc(size * sizeof(char) + 1);
    while(s[i])
    {
        ptr[i] = s[i];
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}