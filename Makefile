NAME = shell

SRC =	main.c export.c export2.c unset.c check_builtins.c signal.c termfunc.c readline.c arrows.c \
		utils.c utils2.c utils3.c utils4.c utils5.c utils6.c utils7.c utils8.c parser_utils.c error.c \
		history.c history2.c lexer.c token.c words.c metachar.c quotes.c envvar.c parser.c parser2.c \
		buildin1.c buildin2.c execs.c pipes.c child.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

$(NAME): $(OBJ)
	${RM} shell
	@gcc -g -Wall -Wextra -Werror -o $(NAME) $(OBJ) -lncurses

all: $(NAME)

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

.PHONY: all clean fclean re