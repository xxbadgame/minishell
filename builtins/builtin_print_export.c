/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:27:44 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/23 20:34:51 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

char *clean_str(char *str)
{
	int i;
	char *new;
	int j;
	int count_quote;
	
	count_quote = 0;
	j = 0;
	i = 0;
	while(str[i++])
	{
		if(str[i] == '"')
			count_quote++;
	}
	i = 0;
	new = malloc(ft_strlen(str) - count_quote + 1);
	while(str[i])
	{
		if(str[i] != '"')
		{
			new[j++] = str[i];
		}
		i++;
	}
	new[j] = '\0';
	return new;
}

int builtin_export_env(t_env *env)
{
	int i;
	char **split;
	int equal_flag;
	
	i = 0;
	equal_flag = 0;
	while(env->env_cpy[i])
	{
		if (ft_strchr(env->env_cpy[i],'=') != 0 
			&& env->env_cpy[i][ft_strchr(env->env_cpy[i],'=') + 1] == '\0') 
			equal_flag = 1;
			
		split = ft_split(env->env_cpy[i],'=');
		if(!split)
			return (-1);
		if(split[0][0] == '_' && ft_strlen(split[0]) == 1)
		{
			i++;
			free_tab(split);
			continue;
		}
		if(equal_flag == 1)
		{
			printf("export %s=\"\"\n", split[0]);
			i++;
			equal_flag = 0;
			free_tab(split);
			continue;
		}
		if (!split[1])
		{
			printf("export %s\n", split[0]);
			i++;
			free_tab(split);
			continue;
		}
		printf("export %s=\"%s\"\n", split[0], split[1]);
		i++;
		free_tab(split);
	}
	return 0;
}
