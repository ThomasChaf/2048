CC=		gcc

BINARY=		../2048.app/Contents/MacOS

SRC_DIR=	Sources

SRC=	$(SRC_DIR)/main.c \
	$(SRC_DIR)/game.c \
	$(SRC_DIR)/asset.c \
	$(SRC_DIR)/grid.c \
	$(SRC_DIR)/score.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/sdl.c

OBJ=		$(SRC:.c=.o)

CFLAGS=		-Wall -Werror -W -Wextra -I./includes

LDFLAGS=	-lmod -framework SDL2 -framework SDL2_ttf

NAME=		$(BINARY)/2048

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
