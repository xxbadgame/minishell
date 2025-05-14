/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:59:49 by engiusep          #+#    #+#             */
/*   Updated: 2025/05/14 15:12:23 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int builtin_pwd()
{
	char *cwd;
	
	cwd = getcwd(NULL,0);
	printf("%sMOI\n",cwd);
	free(cwd);
	return (0);
}
