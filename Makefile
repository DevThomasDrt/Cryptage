.PHONY: clean fclean re

SRC     = cryptage.c

OBJ     = $(SRC:.c=.o)

NAME    = Cryptage

all: $(NAME)

$(NAME): $(OBJ)
		gcc -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all
