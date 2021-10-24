#include "../shell.h"

static char	*ft_getenv(char **env, char *name)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (name[j] && name[j] == env[i][j])
			j++;
		if (env[i][j] == '=')
		{
			str = safe_malloc(sizeof(char) * ft_strlen(&(env[i][j])));
			return (ft_copy(str, &(env[i][j + 1])));
		}
		i++;
	}
	return (NULL);
}

static void	envvar (t_parser *parser, t_token **token, char **word)
{
	int		start;
	char	*name;
	char	*val;

	start = parser->pos - 1;
	if (!ft_isdigit(parser->line[start + 1]))
	{
		while (ft_isalnum(parser->line[parser->pos])
			|| parser->line[parser->pos] == '_')
			parser->pos++;
	}
	parser->pos--;
	if (parser->pos == start)
		return ;
	name = safe_malloc(sizeof(char) * (parser->pos - start + 1));
	ft_strlcpy(name, &(parser->line[start + 1]), parser->pos + 1 - start);
	val = ft_getenv(g_var.env, name);
	if (name)
		free(name);
	name = *word;
	*word = ft_strjoin(*word, val);
	if (name)
		free(name);
	if (val)
		free(val);
}

void	env_variable(t_parser *parser, t_token **token, char **word)
{
	parser->pos++;
	if (parser->line[parser->pos] == '?')
	{
		add_word(token, word, WORD, 0);
		add_token(token, "$?", EXCODE, 0);
	}
	else
		envvar(parser, token, word);
}
