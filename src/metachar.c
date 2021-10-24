#include "../shell.h"

int	check_del(char *buf, int col, char **line)
{
	if (!ft_strcmp(buf, "\177"))
	{
		if (ft_strlen(*line))
		{
			tputs(tgetstr("le", NULL), 1, ft_putchar);
			tputs(tgetstr("dc", NULL), 1, ft_putchar);
			(*line)[ft_strlen(*line) - 1] = '\0';
		}
		return (1);
	}
	return (0);
}

static int	free_redir(int ret, char **redir)
{
	if (*redir)
		free(*redir);
	return (ret);
}

static int	redirchar(t_parser *parser, t_token **token, int start)
{
	char	*redir;

	redir = safe_malloc(sizeof(char) * 3);
	ft_memset(redir, '\0', 3);
	redir[0] = parser->line[parser->pos];
	parser->pos++;
	if ((redir[0] == '>' && parser->line[parser->pos] == '>')
		|| (redir[0] == '<' && parser->line[parser->pos] == '<'))
	{
		redir[1] = parser->line[parser->pos];
		parser->pos++;
	}
	else if (ft_isredir(parser->line[parser->pos]))
		return (free_redir(ft_error(2), &redir));
	while (ft_isspace(parser->line[parser->pos]))
		parser->pos++;
	start = parser->pos;
	while (ft_isalnum(parser->line[parser->pos])
		|| parser->line[parser->pos] == '_'
		|| parser->line[parser->pos] == '.')
		parser->pos++;
	reword(parser, &redir, start);
	parser->pos--;
	add_token(token, redir, REDIR, 0);
	return (free_redir(0, &redir));
}

int	metachar(t_parser *parser, char **word, t_token **token)
{
	int	start;

	if (ft_strlen(*word))
		add_word(token, word, WORD, 0);
	if (ft_isredir(parser->line[parser->pos]))
		return (redirchar(parser, token, start));
	else
	{
		if (!ft_strlen(*word) && ft_ispquotes(parser))
			add_word(token, word, WORD, 1);
		if (parser->line[parser->pos] == '|')
			add_token(token, "|", PIPE, 0);
		else if (parser->line[parser->pos] == ';')
			add_token(token, ";", CONN, 0);
	}
	return (0);
}
