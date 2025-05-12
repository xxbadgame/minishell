/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:32:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/12 13:01:56 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
#include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *s);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*ft_strncat(char *dest, char *src, int n);
int		ft_strlcpy(char *dest, char *src, int size);
void	free_tab(char **tab);
char	*ft_strndup(char *str, int size);
char	*get_next_line(int fd);
int	tab_len(char **tab);
int	ft_strchr(char *str,char c);


#endif