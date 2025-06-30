/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:28:27 by engiusep          #+#    #+#             */
/*   Updated: 2025/06/30 12:51:55 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	check_char2(char *str, int i)
{
	if (str[i] == ' ' || str[i] == '|' || str[i] == '>' || str[i] == '<'
		|| ft_strncmp(str + i, ">>", 2) == 0 || ft_strncmp(str + i, "<<",
			2) == 0)
		return (1);
	return (0);
}

char	*malloc_var_in_env(char *str, t_shell *shell, t_index_lexer *index)
{
	char	*temp;
	char	*var_in_env;

	temp = ft_substr(str, index->i, env_var_checker(str + index->i));
	var_in_env = find_str_in_env(shell->env, temp);
	free(temp);
	if (!var_in_env)
	{
		index->i += env_var_checker(str + index->i);
		return (NULL);
	}
	return (var_in_env);
}

int	add_in_str(char **result, char *var_in_env, t_index_lexer *index)
{
	char	*temp;

	temp = *result;
	*result = ft_joinchar(temp, var_in_env[index->j]);
	if (!(*result))
		return (free(temp), free(var_in_env), -1);
	free(temp);
	return (0);
}

int	dollar_var_env(char **result, t_index_lexer *index, char *str,
		t_shell *shell)
{
	char	*var_in_env;

	var_in_env = malloc_var_in_env(str, shell, index);
	if (!var_in_env)
		return (-1);
	while (var_in_env[index->j] && var_in_env[index->j] == ' ')
		index->j++;
	while (var_in_env[index->j])
	{
		if (add_in_str(result, var_in_env, index) == -1)
			return (-1);
		index->j++;
		if (var_in_env[index->j] == ' ')
		{
			while (var_in_env[index->j] == ' ')
				index->j++;
			if (var_in_env[index->j] == '\0')
				break ;
			else
				return (free(var_in_env), 2);
		}
	}
	if (index->j == ft_strlen(var_in_env))
		index->i += env_var_checker(str + index->i);
	return (free(var_in_env), 0);
}

int	start_loop(char *str, t_index_lexer *index, char **result, t_shell *shell)
{
	int	exit_quote;

	exit_quote = in_quote(str, index, result, shell);
	if (str[index->i] == '\0' && exit_quote)
		return (2);
	if (check_char2(str, index->i) && exit_quote)
		return (2);
	return (0);
}
