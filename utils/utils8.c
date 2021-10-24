#include "../shell.h"

int	ft_isredir(int c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_path(void)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (g_var.env[i])
	{
		if (!(ft_strncmp(g_var.env[i], "PATH=", 5)))
			flag = 1;
		i++;
	}
	return (flag);
}
