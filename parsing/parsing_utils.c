#include "parsing.h"

int	for_redir(t_cmd *current, t_token *tmp)
{
	if (tmp->type == REDIR_IN && tmp->next->type == WORD)
	{
		current->infile = ft_strdup(tmp->next->value);
	}
	else if (tmp->type == REDIR_OUT && tmp->next->type == WORD)
	{
		current->outfile = ft_strdup(tmp->next->value);
		current->append = 0;
	}
	else
	{
		write(2, "ERROR\n", 6);
		return (1);
	}
	return (0);
}

void	for_append(t_cmd *current, t_token *tmp)
{
	current->outfile = ft_strdup(tmp->value);
	current->append = 1;
}

void	command_checker(int *argc, t_token **tmp, t_cmd **current)
{
    t_cmd *new_current;
	if ((*tmp)->type == WORD)
		(*current)->argv[(*argc)++] = ft_strdup((*tmp)->value);
	else if ((*tmp)->type == REDIR_IN || (*tmp)->type == REDIR_OUT)
	{
		for_redir((*current), (*tmp));
		(*tmp) = (*tmp)->next;
	}
	else if ((*tmp)->type == REDIR_APPEND)
	{
		for_append((*current), (*tmp));
		(*tmp) = (*tmp)->next;
	}
	else if ((*tmp)->type == PIPE || (*tmp)->next == NULL)
	{
		(*current)->argv[(*argc)] = NULL;
		new_current = init_cmd(count_elem_cmd((*tmp)->next));
		(*current)->next = new_current;
		(*current) = new_current;
		(*argc) = 0;
	}
}
