#include "shell.h"

int	is_buildin(char *cmd_zero)
{
	if (!(ft_strcmp("pwd", cmd_zero)))
		return (1);
	if (!(ft_strcmp("env", cmd_zero)))
		return (1);
	if (!(ft_strcmp("echo", cmd_zero)))
		return (1);
	if (!(ft_strcmp("export", cmd_zero)))
		return (1);
	return (0);
}

void	exec_buildin(char **cmd_arr)
{
	if (ft_strcmp("echo", *cmd_arr) == 0)
		cmd_echo(cmd_arr);
	if (ft_strcmp("env", *cmd_arr) == 0)
		cmd_env(cmd_arr);
	if (ft_strcmp("pwd", *cmd_arr) == 0)
		cmd_pwd();
	if (ft_strcmp("export", *cmd_arr) == 0)
		cmd_export_without();
	exit(0);
}
