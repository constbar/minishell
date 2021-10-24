#include "../shell.h"

int	ft_ispquotes(t_parser *parser)
{
	int	i;

	i = parser->pos - 1;
	while (i && ft_isspace(parser->line[i]))
		i--;
	if (parser->line[i] == '\'' || parser->line[i] == '\"')
		return (1);
	return (0);
}

static void	escape_char(t_parser *parser, char **word)
{
	parser->pos++;
	if (!(parser->line[parser->pos] == '\\'
			|| parser->line[parser->pos] == '\"'
			|| parser->line[parser->pos] == '$'))
		parser->pos--;
}

int	double_quote(t_parser *parser, char **word, t_token **token)
{
	int		start;

	parser->pos++;
	start = parser->pos;
	while (parser->line[parser->pos] && parser->line[parser->pos] != '\"')
	{
		if (parser->line[parser->pos] == '$')
		{
			reword(parser, word, start);
			env_variable(parser, token, word);
			start = parser->pos + 1;
		}
		else if (parser->line[parser->pos] == '\\')
		{
			reword(parser, word, start);
			escape_char(parser, word);
			start = parser->pos;
		}
		parser->pos++;
	}
	if (parser->line[parser->pos] != '\"')
		return (ft_error(2));
	reword(parser, word, start);
	return (0);
}

int	simple_quote(t_parser *parser, char **word)
{
	int	start;

	parser->line++;
	start = parser->pos;
	while (parser->line[parser->pos] && parser->line[parser->pos] != '\'')
		parser->pos++;
	if (parser->line[parser->pos] != '\'')
		return (ft_error(2));
	reword(parser, word, start);
	return (0);
}
