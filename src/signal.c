#include "../shell.h"

void	handler(int sig)
{
	g_var.signal = 1;
}

void	childhandler(int sig)
{
	kill(g_var.pid, sig);
	if (sig == SIGINT)
		write(1, "\n", 2);
	else if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}

void	ft_interrupt(t_history **history, t_history **cur, char **line)
{
	if (!*history)
		free_history(cur);
	else
		free_history(&((*history)->prev));
	write(1, "\n", 1);
	if (*line)
		free(*line);
	g_var.signal = 0;
}
