#include "../shell.h"

int	history_size(t_history *history)
{
	t_history	*node;
	int			size;

	node = history;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}
