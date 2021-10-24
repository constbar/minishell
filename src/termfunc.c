#include "../shell.h"

void	on_termcap(struct termios *term)
{
	char	*termtype;

	termtype = getenv("TERM");
	if (tgetent(0, termtype) <= 0 || tcgetattr(0, term) < 0)
		exit(3);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_cc[VMIN] = 0;
	term->c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, term);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	off_termcap(struct termios *term)
{
	term->c_lflag |= (ECHO);
	term->c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, term);
	signal(SIGINT, childhandler);
	signal(SIGQUIT, childhandler);
}

int	get_curs(void)
{
	char	buf[10];
	char	*str;
	int		col;

	col = -1;
	write(1, CURSOR_POS, 4);
	ft_memset(buf, '\0', 10);
	if (read(1, buf, 10) < 0)
		ft_error(2);
	else
	{
		str = ft_strchr(buf, ';');
		if (!str || !str[1])
			return (col);
		col = ft_atoi(&str[1]);
	}
	return (col);
}
