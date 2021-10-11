#include "shell.h"

static void	print_buf(char *buf, char **line)
{
	char	*str;
	int		i;

	i = 0;
	while (buf[i])
	{
		if (ft_isprint(buf[i]))
			i++;
		else
			return ;
	}
	write(1, buf, ft_strlen(buf));
	str = *line;
	*line = ft_strjoin(*line, buf);
	if (str)
		free(str);
}

static void	do_enter(t_history **cur, char **line)
{
	if ((*cur)->prev)
		*cur = first_history(*cur);
	if (!ft_strlen(*line))
		free_history(cur);
	else
		change_history(cur, *line);
	if (*line)
		free(*line);
	write(1, "\n", 1);
}

static int	check_buf(t_history **cur, char **line,
						char *buf, int col)
{
	t_history	*node;

	if (!buf)
		return (0);
	if (check_arrows(cur, buf, line, col))
		;
	else if (check_del(buf, col, line))
		;
	else if (!ft_strcmp(buf, "\n"))
	{
		do_enter(cur, line);
		return (1);
	}
	else
		print_buf(buf, line);
	return (0);
}

static void	check_ctrld(char *buf, char *line, struct termios *term)
{
	if (!ft_strcmp(buf, "\04") && !ft_strlen(line))
	{
		off_termcap(term);
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	read_line(t_history **history, int col, struct termios *term)
{
	char		buf[5];
	char		*line;
	t_history	*cur;

	add_history(history, "");
	cur = *history;
	*history = cur->next;
	line = NULL;
	while (!g_var.signal)
	{
		if (!line)
			line = ft_strdup("");
		ft_memset(buf, '\0', 5);
		if (read(0, buf, 4) < 0)
			ft_error(2);
		check_ctrld(buf, line, term);
		if (check_buf(&cur, &line, buf, col))
		{
			if (cur)
				*history = cur;
			return ;
		}
	}
	ft_interrupt(history, &cur, &line);
}
