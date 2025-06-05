NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = main.c \
       fractols.c \
       events.c \
       utils.c \
       init.c

OBJS = $(SRCS:.c=.o)

all: $(MLX) $(NAME)

$(MLX):
	@cd $(MLX_DIR) && ./configure
	@cd $(MLX_DIR) && make

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@cd $(MLX_DIR) && ./configure clean
	rm -f $(OBJS)

fclean: clean
	@cd $(MLX_DIR) && ./configure clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
