/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:27:44 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/15 15:08:10 by engiusep         ###   ########.fr       */
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
	while(str[i])
	{
		if(str[i] == '"')
			count_quote++;
		i++;
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
	char *var;
	char *clean;
	i = 0;

	while(env->env_cpy[i])
	{
		split = ft_split(env->env_cpy[i],'=');
		if(!split)
			return (-1);
		if(split[0][0] == '_' && ft_strlen(split[0]) == 1)
		{
			i++;
			continue;
		}
		if(!split[1])
		{
			printf("export %s\n",clean);
			i++;
			continue;
		}
		else
			var = split[1];
		clean = clean_str(split[1]);
		printf("export %s=\"%s\"\n", split[0], clean);
		free(clean);
		i++;
		free_tab(split);
	}
	return 0;
}
