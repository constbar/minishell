#include "../shell.h"

void	free_history(t_history **history)
{
	t_history	*node;

	node = *history;
	if (node->line)
		free(node->line);
	node->prev = NULL;
	node->next = NULL;
	if (node)
		free(node);
	*history = NULL;
}

void	burn_history(t_history **history)
{
	t_history	*tmp;
	t_history	*node;

	node = *history;
	while (node)
	{
		tmp = node->next;
		free_history(&node);
		node = tmp;
	}
}

void	add_history(t_history **history, char *str)
{
	t_history	*node;

	node = safe_malloc(sizeof(t_history));
	node->prev = NULL;
	if (!ft_strlen(str))
		node->line = ft_strdup("");
	else
		node->line = ft_strdup(str);
	if (*history)
		(*history)->prev = node;
	node->next = *history;
	*history = node;
}

void	change_history(t_history **node, char *str)
{
	t_history	*tmp;

	tmp = *node;
	if (tmp->line)
		free(tmp->line);
	tmp->line = ft_strdup(str);
}

t_history	*first_history(t_history *node)
{
	while (node->prev)
		node = node->prev;
	return (node);
}
