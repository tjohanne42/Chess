C_STANDART = \033[0m
C_GRAS = \033[1m
C_SOULIGN = \033[4m
C_CLIGN = \033[5m
C_SURLIGN = \033[7m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_YELLOW = \033[33m
C_BLUE = \033[34m
C_PINK = \033[35m
C_CYAN = \033[36m
C_GREY = \033[37m

NAME = chess

CC = gcc -Wall -Wextra -Werror

SRC = main.c tools_SDL.C start_game.c print_game.c init_game.c human_left_click.c pred/pred_from_point.c check.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@ make -C lib/ft_printf
	@ $(CC) $(addprefix src/, $(SRC)) -I inc lib/ft_printf/libftprintf.a -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o bin/$(NAME)
	@ echo -e "$(C_STANDART)==\tCompilation $(NAME)\t\t$(C_GREEN)DONE$(C_STANDART)"

clean:
	@ make clean -C lib/ft_printf
	@ echo -e "$(C_STANDART)==\tClean $(NAME)\t\t\t$(C_GREEN)DONE$(C_STANDART)"

fclean:
	@ make fclean -C lib/ft_printf
	@ rm -f bin/$(NAME)
	@ echo -e "$(C_STANDART)==\tFclean $(NAME)\t\t\t$(C_GREEN)DONE$(C_STANDART)"

re: fclean all

test:
	@ rm -f bin/$(NAME)
	@ $(CC) $(addprefix src/, $(SRC)) -I inc lib/ft_printf/libftprintf.a -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o bin/$(NAME)
	@ echo -e "$(C_STANDART)==\tCompilation $(NAME)\t\t$(C_GREEN)DONE$(C_STANDART)"
	./bin/$(NAME)