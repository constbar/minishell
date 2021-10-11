#include "shell.h"

static t_token	*new_token(char *word, int type, int presep)
{
	t_token	*node;

	if (!ft_strlen(word) && !presep)
		return (NULL);
	node = safe_malloc(sizeof(t_token));
	node->next = NULL;
	node->prev = NULL;
	if (!ft_strlen(word))
		node->str = ft_strdup("");
	else
		node->str = ft_strdup(word);
	node->type = type;
	return (node);
}

static t_token	*last_token(t_token *token)
{
	t_token	*node;

	if (!token)
		return (NULL);
	node = token;
	while (node->next)
		node = node->next;
	return (node);
}

void	add_token(t_token **token, char *word, int type, int presep)
{
	t_token	*node;

	if (!*token)
		*token = new_token(word, type, presep);
	else
	{
		node = last_token(*token);
		node->next = new_token(word, type, presep);
	}
}

void	free_token(t_token **token)
{
	t_token	*node;

	node = *token;
	if (node->str)
		free(node->str);
	node->prev = NULL;
	node->next = NULL;
	if (node)
		free(node);
	node = NULL;
}

void	burn_token(t_token **token)
{
	t_token	*tmp;
	t_token	*node;

	node = *token;
	while (node)
	{
		tmp = node->next;
		free_token(&node);
		node = tmp;
	}
}
