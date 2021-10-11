#include "shell.h"

void	close_pipes(int pipes[][2], int num_pipes)
{
	int	k;

	k = 0;
	while (k < num_pipes)
	{
		close(pipes[k][0]);
		close(pipes[k][1]);
		k++;
	}
}

void	child(t_cmd **master, int i, int pipes[][2], int num_pipes)
{
	int	k;
	int	q;

	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	else if (master[i]->input)
	{
		dup2(master[i]->input, STDIN_FILENO);
		close(master[i]->input);
	}
	if (i < (num_pipes + 1) - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	else if (master[i]->output)
	{
		dup2(master[i]->output, STDOUT_FILENO);
		close(master[i]->output);
	}
	close_pipes(pipes, num_pipes);
	exec_cmd(master[i]->arg, i, k, q);
}
