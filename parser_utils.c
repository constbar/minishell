#include "shell.h"

int	nbrtype(t_token *token, int count, int sep)
{
	t_token	*node;
	int		n;

	n = 1;
	node = token;
	while (node && node->type != sep)
	{
		if (node->type == count || !count)
			n++;
		node = node->next;
	}
	return (n);
}

t_cmd	**malloc_master(t_token *token)
{
	int		np;
	t_cmd	**master;

	np = nbrtype(token, PIPE, CONN);
	master = safe_malloc(sizeof(t_cmd *) * (np + 1));
	master[np] = NULL;
	return (master);
}

t_cmd	*malloc_cmd(void)
{
	t_cmd	*cmd;

	cmd = safe_malloc(sizeof(t_cmd));
	ft_memset(cmd, 0, sizeof(t_cmd));
	return (cmd);
}

static void	free_arr(char ***arg)
{
	int	j;

	j = 0;
	while (*arg && (*arg)[j])
	{
		free((*arg)[j]);
		j++;
	}
}

void	free_master(t_cmd ***master)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = (*master)[i];
	while (cmd)
	{
		free_arr(&(cmd->arg));
		free_arr(&(cmd->stopword));
		free(cmd->arg);
		free(cmd->stopword);
		free(cmd);
		i++;
		cmd = (*master)[i];
	}
	if (*master)
		free(*master);
}
