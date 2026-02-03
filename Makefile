#### VARIABLES ####
NAME = fdf
LIBFT = ./libft/libft.a
MLX = ./minilibx-linux/libmlx.a
# HEADER_PATH = include
CC= cc
# CFLAGS=-Wall -Wextra -Werror -I $(HEADER0_PATH)
CFLAGS=-Wall -Wextra -Werror -Wno-incompatible-pointer-types
# OBJ=ft_*.c =.o
# SRCS = $(HEADER_PATH)ft_atoi
#### SOURCE ####
SRC_FILES = parsing.c \
		draw.c \
		event.c

OBJ_FILES = $(SRC_FILES:.c=.o)
# OBJ_FILES = $(addsuffix .o, $(SRC_FILES))
#### RULES ####
all: ${NAME}


${NAME} : ${LIBFT} ${MLX} ${OBJ_FILES} 
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -L./minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ -g3

${LIBFT} :
	$(MAKE) -C ./libft

${MLX} :
	$(MAKE) -C ./minilibx-linux CFLAGS="-O3 -w -std=gnu89 -fpermissive"

clean:
	rm -f ${OBJ_FILES}
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f ${NAME}
	$(MAKE) -C ./libft fclean

re: fclean  all

.PHONY: all clean fclean re 
