#include "../shell.h"

int	ft_error(int st)
{
	g_var.status = st;
	if (st == 2)
	{
		g_var.status = 258;
		write(2, "syntax error\n", 13);
	}
	else if (st == 1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else if (st == -1)
		write(2, "\nᕕ( ᐛ )ᕗ\n", ft_strlen("\nᕕ( ᐛ )ᕗ\n"));
	else
		write(2, "Error\n", 6);
	return (1);
}

static int	sep_error(int type)
{
	if (type == PIPE || type == CONN)
	{
		ft_error(2);
		return (1);
	}
	return (0);
}

int	parser_errors(t_token *token)
{
	t_token	*node;

	node = token;
	if (!node)
		return (1);
	if (sep_error(node->type))
		return (1);
	while (node->next)
	{
		if ((node->type == CONN || node->type == PIPE)
			&& ((node->next)->type == PIPE
				|| (node->next)->type == CONN))
		{
			ft_error(2);
			return (1);
		}
		node = node->next;
	}
	if (node->type == PIPE)
	{
		ft_error(2);
		return (1);
	}
	return (0);
}
