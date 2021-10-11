#include "shell.h"

t_global	g_var;

static t_token	*parse_lexer(char *line)
{
	t_parser	parser;
	t_token		*token;
	int			start;

	parser.line = line;
	parser.pos = 0;
	start = 0;
	token = ft_lexer(&parser, start);
	if (parser_errors(token))
	{
		if (token)
			burn_token(&token);
		return (NULL);
	}
	return (token);
}

static void	parse_execute(char *line)
{
	t_token		*token;
	t_token		*tok;
	int			nc;
	t_cmd		**master;
	int			i;

	token = parse_lexer(line);
	if (!token)
		return ;
	nc = nbrtype(token, CONN, 0);
	tok = token;
	while (nc--)
	{
		master = master_work(&tok);
		if (master)
		{
			if ((*master)->arg)
			{
				g_var.status = 0;
				execute_master(master, i);
			}
			free_master(&master);
		}
	}
	burn_token(&token);
}

static void	ft_loop(void)
{
	t_history		*history;
	struct termios	term;
	int				size;
	int				curs;

	history = NULL;
	size = 0;
	while (1)
	{
		write(1, "shelly$ ", 8);
		on_termcap(&term);
		curs = get_curs();
		if (curs < 0)
		{
			ft_error(-1);
			continue ;
		}
		read_line(&history, curs, &term);
		off_termcap(&term);
		if (size < history_size(history))
		{
			size++;
			parse_execute(history->line);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	ft_memset(&g_var, 0, sizeof(t_global));
	cpy_env(env);
	ft_loop();
	return (0);
}
