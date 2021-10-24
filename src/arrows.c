#include "../shell.h"

static void	up_down(t_history **cur, char **line, int ud, int col)
{
	if (ft_strcmp((*cur)->line, *line))
		change_history(cur, *line);
	if (ud)
	{
		if (!(*cur)->next)
			return ;
		else
			*cur = (*cur)->next;
	}
	else
	{
		if (!(*cur)->prev)
			return ;
		else
			*cur = (*cur)->prev;
	}
	tputs(tgoto(tgetstr("ch", NULL), 1, col - 1), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	write(1, (*cur)->line, ft_strlen((*cur)->line));
	if (*line)
		free(*line);
	*line = ft_strdup((*cur)->line);
}

int	check_arrows(t_history **cur, char *buf, char **line, int col)
{
	if (!ft_strcmp(buf, ARROW_UP))
		up_down(cur, line, 1, col);
	else if (!ft_strcmp(buf, ARROW_DOWN))
		up_down(cur, line, 0, col);
	else
		return (0);
	return (1);
}
