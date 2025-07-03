/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:46:05 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/03 10:15:06 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../terminal.h"

int	check_lex_in_loop(char *str, t_index_lexer *index, char **result,
		t_shell *shell)
{
	if (str[index->i + 1] && str[index->i] == '$' 
		&& str[index->i + 1] == '?' && index->expand_heredoc == 0)
		after_dollar_checker(index, result, shell);
	else if (str[index->i] == '$' && ft_isalpha(str[index->i + 1]) == 0
		&& index->expand_heredoc == 0)
		index->i += 2;
	else if (str[index->i] == '$' && env_var_checker(str + index->i) != 0
		&& index->expand_heredoc == 0)
	{
		if (in_quote_var_env(result, shell, index, str) == 1)
			return (2);
	}
	else
		end_loop(result, str, index);
	return (0);
}
