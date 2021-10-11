#include "shell.h"

void	cmd_echo(char **cmd_arr)
{
	int	i;

	if (cmd_arr[1] && (!(ft_strcmp(cmd_arr[1], "-n"))) && !cmd_arr[2])
		return ;
	if (cmd_arr[1] && (!(ft_strcmp(cmd_arr[1], "-n"))) && cmd_arr[2])
	{
		i = 2;
		while (cmd_arr[i])
		{
			if (cmd_arr[i + 1] == NULL)
				ft_putstr(cmd_arr[i]);
			else
			{
				ft_putstr(cmd_arr[i]);
				ft_putstr(" ");
			}
			i++;
		}
	}
	else if (cmd_arr[1] == NULL)
		ft_putstr("\n");
	else
		echo_else(cmd_arr);
}

void	echo_else(char **cmd_arr)
{
	int	i;

	i = 1;
	while (cmd_arr[i] != NULL)
	{
		if (cmd_arr[i + 1] == NULL)
		{
			ft_putstr(cmd_arr[i]);
			ft_putstr("\n");
		}
		else
		{
			ft_putstr(cmd_arr[i]);
			ft_putstr(" ");
		}
		i++;
	}
}

void	cmd_env(char **cmd_arr)
{
	int	i;

	i = 0;
	if (cmd_arr[1] != NULL)
	{
		ft_putstr("env: ");
		ft_putstr(cmd_arr[1]);
		ft_putstr(": No such file or directory\n");
		g_var.status = 127;
		return ;
	}
	while (g_var.env[i])
	{
		if (first_app(g_var.env[i]) > 0)
		{
			ft_putstr(g_var.env[i]);
			ft_putstr("\n");
		}
		i++;
	}
}
