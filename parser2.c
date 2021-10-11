#include "shell.h"

static void	add_stop(t_token *token, t_cmd **master, int i)
{
	(*master)->stopword = safe_malloc(sizeof(char *) * (i + 2));
	ft_memset((*master)->stopword, 0, (i + 2) * sizeof(char *));
	(*master)->stopword[i] = ft_strdup(token->str);
	(*master)->stopword[i + 1] = NULL;
}

void	volcano(t_token *token, t_cmd **master)
{
	int		i;
	char	**pain;

	i = 0;
	if (!((*master)->stopword))
		add_stop(token, master, 0);
	else
	{
		while ((*master)->stopword[i])
			i++;
		pain = (*master)->stopword;
		add_stop(token, master, i);
		while (i > 0)
		{
			i--;
			(*master)->stopword[i] = pain[i];
		}
		if (pain)
			free(pain);
	}
}
