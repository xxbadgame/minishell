/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:59:49 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/21 12:58:47 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int builtin_pwd()
{
	char *cwd;
	
	cwd = getcwd(NULL,0);
	printf("%s\n",cwd);
	free(cwd);
	return (0);
}
