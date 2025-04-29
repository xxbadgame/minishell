/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:46:41 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/04/29 14:53:31 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "../libft/libft.h"

typedef struct s_env
{
	char **env_cpy;
	char **path_edit;
} 	t_env;

t_env *init_env(char **envp);
char **create_path(char **env_cpy);
void ft_get_path(t_env *env);

#endif