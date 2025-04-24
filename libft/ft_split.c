/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:29 by engiusep          #+#    #+#             */
/*   Updated: 2025/04/24 10:40:31 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_word(char const *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != sep && s[i + 1] == sep)
			|| (s[i] != sep && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	ft_len_words(char const *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] != sep && s[i] != '\0')
		i++;
	return (i);
}

char	*allocate_copy(char const *str, char sep)
{
	int		i;
	char	*copy_word;

	i = 0;
	copy_word = malloc(ft_len_words(str, sep) + 1);
	if (!copy_word)
		return (NULL);
	while (str[i] != sep && str[i] != '\0')
	{
		copy_word[i] = str[i];
		i++;
	}
	copy_word[i] = '\0';
	return (copy_word);
}

void	ft_free_all(char **spl, int i)
{
	int	j;

	j = 0;
	while (j <= i)
		free(spl[j++]);
	free(spl);
}

char	**ft_split(char const *s, char c)
{
	int		nb_words;
	char	**split;
	int		i;

	i = 0;
	nb_words = ft_count_word(s, c);
	split = malloc((nb_words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (i < nb_words)
	{
		while (*s == c)
			s++;
		split[i] = allocate_copy(s, c);
		if (!split[i])
		{
			ft_free_all(split, i);
			return (NULL);
		}
		while (*s != c && *s != '\0')
			s++;
		i++;
	}
	split[i] = NULL;
	return (split);
}