/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:59:49 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/24 16:48:43 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	if (write(STDOUT_FILENO, cwd, strlen(cwd)) == -1
		|| write(STDOUT_FILENO, "\n", 1) == -1)
	{
		perror("write");
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
