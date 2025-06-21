# parser needs to check if vectors are normalized !
#
#
#
#

CC = cc #-Wall -Wextra -Werror

NAME = miniRT

HDR = miniRT.h

SRC = 	src/main.c \
		src/tools/strutils_0.c \
		src/tools/strutils_1.c \
		src/tools/strutils_2.c \
		src/tools/split.c \
		src/tools/mlxutils_0.c \
		src/tools/memutils_0.c \
		src/tools/memutils_1.c \
		src/tools/links.c \
		src/tools/futils.c \
		src/parser/parser.c \
		src/parser/extract.c \
		src/parser/extract_utils.c \
		src/parser/extract_objs.c \
		src/tracer/tracer.c \
		src/tracer/vector.c \
		src/tracer/vector_utils.c \
		src/tracer/plane.c \
		src/tracer/sphere.c \
		src/tracer/cylinder.c \
		src/tracer/color.c

OBJ = $(SRC:.c=.o)

LIBMLX = src/libmlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLX)
	$(CC) $(OBJ) $(LIBMLX) -lm -lX11 -lXext -o $(NAME)

%.o: %.c $(HDR)
	$(CC) -c $< -o $@

$(LIBMLX):
	make -C src/libmlx

clean:
	make clean -C src/libmlx
	rm -rf $(LIBMLX)
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean