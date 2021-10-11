#include "shell.h"

static void	pipe_helper(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_putstr("streams pipe error\n");
			g_var.status = 86;
			exit(86);
		}
		i++;
	}
}

static void	fork_err(void)
{
	ft_putstr("fork error\n");
	g_var.status = 10;
	exit(10);
}

static pid_t	*fork_time(t_cmd **master, int num_pipes, int pipes[][2])
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = safe_malloc(sizeof(pid_t) * (num_pipes + 1));
	while (i < (num_pipes + 1))
	{
		pid[i] = fork();
		g_var.pid = pid[i];
		if (pid[i] < 0)
			fork_err();
		else if (pid[i] == 0)
			child(master, i, pipes, num_pipes);
		i++;
	}
	return (pid);
}

static void	status_control(int status, int num_pipes, int i)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	if (status && status != 141 && i < num_pipes)
		g_var.status = 1;
	else if (status && status != 141)
		g_var.status = status;
}

void	pipe_handler(t_cmd **master, int num_pipes)
{
	int		i;
	int		status;
	pid_t	*pid;

	int (*pipes)[2];
	pipes = safe_malloc(sizeof(int) * (num_pipes * 2));
	pipe_helper(pipes, num_pipes);
	pid = fork_time(master, num_pipes, pipes);
	close_pipes(pipes, num_pipes);
	i = 0;
	while (i < num_pipes + 1)
	{
		g_var.pid = pid[i];
		waitpid(g_var.pid, &status, 0);
		status_control(status, num_pipes, i);
		i++;
	}
	if (pipes)
		free(pipes);
	if (pid)
		free(pid);
}
