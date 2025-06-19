/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:32:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/19 12:40:55 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_joinchar(char *s1, char c);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*ft_strncat(char *dest, char *src, int n);
int		ft_strcpy(char *dest, char *src);
void	free_tab(char **tab);
char	*ft_strndup(char *str, int size);
char	*get_next_line(int fd);
int		tab_len(char **tab);
int		ft_strchr(char *str, char c);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	print_error(char *prefix, char *arg, char *suffix);
int		ft_isalpha(int c);
int		ft_isnum(char *str);
int		ft_atoi(char *str);
int		ft_isalnum(int character);

#endif