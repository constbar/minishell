#include "shell.h"

void	execute_master(t_cmd **master, int num_pipes)
{
	if (!(ft_strcmp((*master)->arg[0], "exit")))
	{
		cmd_exit((*master)->arg);
		return ;
	}
	if (!(ft_strcmp((*master)->arg[0], "cd")))
	{
		cmd_cd((*master)->arg);
		return ;
	}
	if (!(ft_strcmp((*master)->arg[0], "unset")))
	{
		unsent_all((*master)->arg);
		return ;
	}
	if ((!(ft_strcmp((*master)->arg[0], "export"))) \
	&& ((*master)->arg[1] != NULL))
	{
		export_all((*master)->arg);
		return ;
	}	
	num_pipes = 0;
	while (master[num_pipes + 1] != NULL)
		num_pipes++;
	pipe_handler(master, num_pipes);
}

static void	exec_helper(char **part, char **list_cmd)
{
	char	*tmp;

	tmp = ft_strjoin(*part, "/");
	free(*part);
	*part = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(*part, list_cmd[0]);
	execve(tmp, list_cmd, g_var.env);
	free(tmp);
}

void	exec_cmd(char **list_cmd, int i, int exec_cmd, int size_parts)
{
	char	*tmp;
	char	**parts;

	i = 0;
	size_parts = 0;
	if (is_buildin(list_cmd[0]))
		exec_buildin(list_cmd);
	if (check_path())
	{
		tmp = getenv("PATH");
		parts = ft_split(tmp, ':');
		while (parts[size_parts])
			size_parts++;
		check_sl_join(parts, list_cmd);
	}
	while (i < size_parts)
	{
		exec_helper(&parts[i], list_cmd);
		i++;
	}
	if ((i == size_parts) && (exec_cmd == -1))
		exec_err(list_cmd[0], ": command not found\n", 127);
	else
		exec_err(list_cmd[0], ": No such file or directory\n", 127);
}

void	check_sl_join(char **parts, char **list_cmd)
{
	int			i;
	int			cmp;
	char		*tmp;
	int			exec_cmd;
	struct stat	buff;

	if (list_cmd[0][0] == '.' && list_cmd[0][1] == '/')
		exec_cmd = execve(list_cmd[0], list_cmd, g_var.env);
	i = 0;
	while (parts[i])
	{
		stat(list_cmd[0], &buff);
		if (S_ISDIR(buff.st_mode))
			exec_err(list_cmd[0], ": is a directory\n", 126);
		tmp = ft_strjoin(parts[i], "/");
		cmp = ft_strncmp(tmp, list_cmd[0], ft_strlen(tmp));
		if (!cmp)
			exec_cmd = execve(list_cmd[0], list_cmd, g_var.env);
		free(tmp);
		i++;
	}
}

void	exec_err(char *cmd, char *err, int ex)
{
	write(2, cmd, ft_strlen(cmd));
	ft_putstr(err);
	exit(ex);
}
