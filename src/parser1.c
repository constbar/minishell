#include "../shell.h"

static int	parse_redir(t_token *token, t_cmd **master)
{
	if (!token->str[1] || (!token->str[2] && ft_isredir(token->str[1])))
		return (ft_error(2));
	if (token->str[0] == '<')
	{
		if ((*master)->input)
			close((*master)->input);
		if (token->str[0] == '<' && token->str[1] == '<')
			volcano(token, master);
		else
			(*master)->input = open(&(token->str[1]), O_RDONLY);
	}
	else
	{
		if ((*master)->output)
			close((*master)->output);
		if (token->str[0] == '>' && token->str[1] == '>')
			(*master)->output = open(&(token->str[2]),
					O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			(*master)->output = open(&(token->str[1]),
					O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	if ((*master)->input < 0 || (*master)->output < 0)
		return (ft_error(1));
	return (0);
}

static int	parse_cmd(t_token *token, t_cmd **master, int nt)
{
	if (!((*master)->arg))
	{
		nt = nbrtype(token, 0, PIPE);
		(*master)->arg = safe_malloc(sizeof(char *) * (nt + 1));
		ft_memset((*master)->arg, 0, (nt + 1) * sizeof(char *));
		(*master)->arg[nt] = NULL;
		nt = 0;
	}
	if (token->type == EXCODE)
		(*master)->arg[nt] = ft_itoa(g_var.status);
	else
		(*master)->arg[nt] = ft_strdup(token->str);
	return (nt + 1);
}

t_cmd	**redir_error(t_token **token, t_cmd ***master)
{
	while (*token && (*token)->type != CONN)
		*token = (*token)->next;
	if (*token)
		*token = (*token)->next;
	free_master(master);
	return (NULL);
}

t_cmd	**master_work(t_token **token)
{
	int		np;
	int		nt;
	t_cmd	**master;

	np = 0;
	master = malloc_master(*token);
	master[0] = malloc_cmd();
	while (*token && (*token)->type != CONN)
	{
		if ((*token)->type == PIPE)
			master[++np] = malloc_cmd();
		else if ((*token)->type == REDIR)
		{
			if (parse_redir(*token, &(master[np])))
				return (redir_error(token, &master));
		}
		else
			nt = parse_cmd(*token, &(master[np]), nt);
		(*token) = (*token)->next;
	}
	if (*token)
		(*token) = (*token)->next;
	return (master);
}
