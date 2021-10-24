#include "../shell.h"

static int	do_special(t_parser *parser, char **word, t_token **token)
{
	if (parser->line[parser->pos] == '\'')
		 return (simple_quote(parser, word));
	else if (parser->line[parser->pos] == '\"')
		return (double_quote(parser, word, token));
	else if (parser->line[parser->pos] == '$')
		env_variable(parser, token, word);
	else if (ft_isspace(parser->line[parser->pos]))
	{
		add_word(token, word, WORD, 0);
		while (ft_isspace(parser->line[parser->pos + 1]))
			parser->pos++;
	}
	else if (ft_ismetachar(parser->line[parser->pos]))
		return (metachar(parser, word, token));
	else if (parser->line[parser->pos] == '\\')
	{
		parser->pos += 2;
		reword(parser, word, parser->pos - 1);
		parser->pos--;
	}
	return (0);
}

static int	check_special(t_parser *parser)
{
	if (parser->line[parser->pos] == '\''
		|| parser->line[parser->pos] == '\"'
		|| parser->line[parser->pos] == '$'
		|| ft_isspace(parser->line[parser->pos])
		|| ft_ismetachar(parser->line[parser->pos])
		|| parser->line[parser->pos] == '\\')
		return (1);
	return (0);
}

static void	have_lastword(t_parser *parser, t_token **token, char *word)
{
	if (!ft_strlen(word) && ft_ispquotes(parser))
		add_token(token, word, WORD, 1);
	else
		add_token(token, word, WORD, 0);
}

static t_token	*the_ducks(t_token **token, char **word)
{
	burn_token(token);
	if (*word)
		free(*word);
	return (NULL);
}

t_token	*ft_lexer(t_parser *parser, int start)
{
	char	*word;
	t_token	*token;

	word = NULL;
	token = NULL;
	while (parser->line[parser->pos])
	{
		if (!word)
			word = ft_strdup("");
		if (check_special(parser))
		{
			reword(parser, &word, start);
			if (do_special(parser, &word, &token))
				return (the_ducks(&token, &word));
			start = parser->pos + 1;
		}
		parser->pos++;
	}
	reword(parser, &word, start);
	have_lastword(parser, &token, word);
	if (word)
		free(word);
	return (token);
}
