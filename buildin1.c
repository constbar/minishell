#include "shell.h"

void	cmd_pwd(void)
{
	char	buf[1024];

	ft_putstr(getcwd(buf, sizeof(buf)));
	ft_putstr("\n");
}

void	cmd_exit(char **cmd_arr)
{
	if (cmd_arr[1] != NULL)
	{
		if (str_is_digit(cmd_arr[1]) && cmd_arr[2] == NULL)
		{
			ft_putstr("exit\n");
			g_var.status = 0;
			exit(EXIT_SUCCESS);
		}
		if (!(str_is_digit(cmd_arr[1])))
			exit_if(cmd_arr[1]);
		if (cmd_arr[2])
		{
			ft_putstr("exit\nexit: too many arguments\n");
			g_var.status = 1;
			return ;
		}
	}
	ft_putstr("exit\n");
	g_var.status = 0;
	exit(EXIT_SUCCESS);
}

void	exit_if(char *arr1)
{
	ft_putstr("exit\nexit: ");
	ft_putstr(arr1);
	ft_putstr(" numeric argument required\n");
	g_var.status = 255;
	exit(255);
}

void	cmd_cd(char **cmd_arr)
{
	int		dir;
	char	*home_dir;

	if (cmd_arr[1] == NULL || (!(ft_strcmp(cmd_arr[1], "~"))))
	{
		home_dir = getenv("HOME");
		dir = chdir(home_dir);
	}
	else if (cmd_arr[2])
	{
		cd_print(cmd_arr[2]);
		g_var.status = 1;
		return ;
	}
	else if (cmd_arr[1])
	{
		dir = chdir(cmd_arr[1]);
	}
	if (dir < 0)
	{
		cd_print(cmd_arr[1]);
		g_var.status = 1;
		return ;
	}
}

void	cd_print(char *str)
{
	ft_putstr("cd: ");
	ft_putstr(str);
	ft_putstr(" No such file or directory\n");
}
