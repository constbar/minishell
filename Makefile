NAME = shell

SRC =	src/main.c src/export.c src/export2.c src/unset.c src/check_builtins.c \
		src/signal.c src/termfunc.c src/readline.c src/arrows.c src/error.c \
		src/history.c src/history2.c src/lexer.c src/token.c src/words.c \
		src/metachar.c src/quotes.c src/envvar.c src/parser.c src/parser2.c \
		src/buildin1.c src/buildin2.c src/execs.c src/pipes.c src/child.c \
		utils/utils.c utils/utils2.c utils/utils3.c utils/utils4.c utils/utils5.c \
		utils/utils6.c utils/utils7.c utils/utils8.c utils/parser_utils.c

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