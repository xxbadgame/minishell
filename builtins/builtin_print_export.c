/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:27:44 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/19 12:35:57 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

char	*clean_str(char *str)
{
	int		i;
	char	*new;
	int		j;
	int		count_quote;

	count_quote = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			count_quote++;
		i++;
	}
	i = 0;
	new = malloc(ft_strlen(str) - count_quote + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

static void	print_export_line(char **split, int equal_flag)
{
	if (equal_flag == 1 && !split[1])
	{
		printf("export %s=\"\"\n", split[0]);
		free_tab(split);
		return ;
	}
	if (!split[1])
	{
		printf("export %s\n", split[0]);
		free_tab(split);
		return ;
	}
	printf("export %s=\"%s\"\n", split[0], split[1]);
	free_tab(split);
}

int	builtin_export_env(t_env *env)
{
	int		i;
	char	**split;
	int		equal_flag;

	i = 0;
	while (env->env_cpy[i])
	{
		equal_flag = 0;
		if (ft_strchr(env->env_cpy[i], '=') != 0
			&& env->env_cpy[i][ft_strchr(env->env_cpy[i], '=') + 1] == '\0')
			equal_flag = 1;
		split = ft_split(env->env_cpy[i], '=');
		if (!split)
			return (-1);
		if (split[0][0] == '_' && ft_strlen(split[0]) == 1)
		{
			free_tab(split);
			i++;
			continue ;
		}
		print_export_line(split, equal_flag);
		i++;
	}
	return (0);
}
