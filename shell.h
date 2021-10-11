#ifndef SHELL_H
# define	SHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <term.h>
# include <signal.h>
# include <ncurses.h>
# include <string.h>

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define CURSOR_POS	"\033[6n"
# define ARROW_UP	"\033[A"
# define ARROW_DOWN	"\033[B"

# define SIGINT  2
# define SIGQUIT 3

# define WORD	1
# define ENV	2
# define REDIR	3
# define PIPE	4
# define CONN	5
# define EXCODE	6

typedef struct s_global
{
	int		signal;
	int		status;
	pid_t	pid;
	char	**env;
}				t_global;

extern t_global	g_var;

typedef struct s_history
{
	char				*line;
	struct s_history	*prev;
	struct s_history	*next;
}				t_history;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
}				t_token;

typedef struct s_parser
{
	char	*line;
	int		pos;
}				t_parser;

typedef struct s_cmd
{
	char	**arg;
	int		input;
	int		output;
	char	**stopword;
}				t_cmd;

//termfunc
void			on_termcap(struct termios *term);
void			off_termcap(struct termios *term);
int				get_curs(void);

//signal
void			handler(int sig);
void			childhandler(int sig);
void			ft_interrupt(t_history **history,
					t_history **cur, char **line);

//utils
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *s);
char			*ft_strjoin(const char *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_strcmp(const char *s1, const char *s2);

//utils2
void			*ft_memset(void *str, int c, size_t n);
int				ft_putchar(int c);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *str, int c);
int				ft_isprint(int c);

//util3
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_ismetachar(int c);
int				ft_isspace(int c);

//util4
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_copy(char *dst, char *src);
int				ft_tolower(int c);
void			*safe_malloc(size_t size);
char			*ft_itoa(int nbr);

//util8
int				ft_isredir(int c);

//error
int				ft_error(int st);
int				parser_errors(t_token *token);

//history
void			free_history(t_history **history);
//void 			burn_history(t_history **history);
void			add_history(t_history **history, char *str);
void			change_history(t_history **node, char *str);
t_history		*first_history(t_history *node);

//history2
int				history_size(t_history *history);

//readline
void			read_line(t_history **history, int col,
					struct termios *term);

//arrows
int				check_arrows(t_history **cur, char *buf, char **line, int col);

//lexer
t_token			*ft_lexer(t_parser *parser, int start);

//token
void			add_token(t_token **token, char *word, int type, int presep);
void			free_token(t_token **token);
void			burn_token(t_token **token);

//words
void			add_word(t_token **token, char **word, int type, int presep);
void			reword(t_parser *parser, char **word, int start);

//metachar
int				check_del(char *buf, int col, char **line);
int				metachar(t_parser *parser, char **word, t_token **token);

//quotes
int				ft_ispquotes(t_parser *parser);
int				double_quote(t_parser *parser, char **word, t_token **token);
int				simple_quote(t_parser *parser, char **word);

//envvar
void			env_variable(t_parser *parser, t_token **token, char **word);

//parser
t_cmd			**master_work(t_token **token);

//parser2
void			volcano(t_token *token, t_cmd **master);

//parser_utils
int				nbrtype(t_token *token, int count, int sep);
t_cmd			**malloc_master(t_token *token);
t_cmd			*malloc_cmd(void);
void			free_master(t_cmd ***master);

// kostya

// utils 5
int				first_app(char *str);
int				str_is_digit(char *str);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);

// utils 6
char			**ft_split(char const *s, char c);
void			*ft_calloc(size_t n, size_t size);

// utils 7
void			ft_bzero(void *s, size_t n);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
void			cpy_env(char **env);
void			ft_putstr(char *s);

void			execute_master(t_cmd **master, int i);
void			redir_handler(t_cmd *master);
void			pipe_handler(t_cmd **master, int num_pipes);

void			exec_cmd(char **master_arr, int i,
					int exec_cmd, int size_parts);

// child
void			close_pipes(int pipes[][2], int	num_pipes);
void			child(t_cmd **master, int i,
					int pipes[][2], int num_pipes);

// exec part
void			cmd_pwd(void);
int				check_path(void);
void			exit_if(char *arr1);
void			cd_print(char *str);
void			cmd_cd(char **cmd_arr);
void			cmd_env(char **cmd_arr);
void			cmd_export_without(void);
void			cmd_echo(char **cmd_arr);
void			cmd_exit(char **cmd_arr);
void			echo_else(char **cmd_arr);
void			unsent_all(char **cmd_arr);
void			export_all(char **cmd_arr);
void			cmd_export(char **cmd_arr);
int				is_buildin(char *cmd_zero);
void			exec_buildin(char **cmd_arr);
void			cmd_unset(char *cmd_arr, int k);
void			cmd_unset_for_str(char *cmd_arr);
void			exec_err(char *cmd, char *err, int ex);
void			check_sl_join(char **partsi, char **list_cmd);
void			cmd_export_with_arg(char *cmd_arr, int fa, int bp, int k);

#endif
