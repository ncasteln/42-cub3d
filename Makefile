NAME = cub3d
LIBFT_A = lib/libft/libft.a
# CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	= lib/MLX42
HEADERS	= -I ./inc -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm lib/libft/libft.a -L./lib/libft -lft
SRCS = cub3d.c hooks.c utils.c
OBJS	= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBS): libmlx libft

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	make -C lib/libft

%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	make fclean -C lib/libft
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx libft