#include "../shell.h"

void	add_word(t_token **token, char **word, int type, int presep)
{
	add_token(token, *word, type, presep);
	if (*word)
		free(*word);
	*word = ft_strdup("");
}

void	reword(t_parser *parser, char **word, int start)
{
	char	*str;
	char	*sub;

	str = *word;
	sub = ft_substr(parser->line, start, parser->pos - start);
	*word = ft_strjoin(*word, sub);
	if (sub)
		free(sub);
	if (str)
		free(str);
}
