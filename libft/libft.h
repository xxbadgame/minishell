/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:32:46 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/05 10:16:04 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strncmp(const char *s1, const char *s2, int n);
char 	*ft_strdup(char *s);
int 	ft_strlen(char *str);
char	**ft_split(char const *s, char c);
int		ft_tablen(char **tab);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin3(char *s1, char c, char *s2);
