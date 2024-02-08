# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 08:59:00 by ncasteln          #+#    #+#              #
#    Updated: 2024/02/08 12:51:29 by ncasteln         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra #-Werror

LIB = $(LIBFT) $(FT_PRINTF) $(GNL)
LIBFT = ./lib/libft/libft.a
FT_PRINTF = ./lib/ft_printf/libftprintf.a
GNL = ./lib/get_next_line/libgnl.a
MLX42 = ./lib/MLX42/build/libmlx42.a
GLFW = -lglfw

INCLUDE = -I./include/ \
	-I./lib/libft/include/ \
	-I./lib/ft_printf/include/ \
	-I./lib/get_next_line/ \
	-I./lib/MLX42/include/MLX42/

VPATH = ./src/ \
	./src/parser/ \
	./src/utils/ \
	./src/raycast/ \
	./src/minimap/ \

PARSER = parse.c \
	parse_file_content.c \
	parse_assets.c \
	extract_asset_value.c \
	extract_color_utils.c \
	parse_map.c \
	parse_player.c \
	path_validation.c \
	parse_assets_utils.c \
	check_behind_doors.c \
	rectangolize.c \

UTILS = err_free_exit.c \
	print_map.c \
	print_assets.c \
	free_utils.c \
	is_blank_line.c \
	init_structs.c \

RAYCAST = raycast.c \
	hooks.c \
	utils.c \
	move.c \
	spritecast.c \
	sprites.c \

MINIMAP = draw_minimap.c \

SRC = cub3d.c \
	$(PARSER) \
	$(UTILS) \
	$(RAYCAST) \
	$(MINIMAP)

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

# --------------------------------------------------------------- BONUS VERSION
IS_BONUS = -DBONUS=0
ifeq ($(filter bonus,$(MAKECMDGOALS)),bonus)
	IS_BONUS = -DBONUS=1
endif
ifeq ($(filter test_bonus,$(MAKECMDGOALS)),test_bonus)
	IS_BONUS = -DBONUS=1
endif

# ----------------------------------------------------------------- BASIC RULES
all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIB) $(MLX42) $(OBJS)
	@echo "$(NC)Compiling $@ executable file..."
	@$(CC) $(CFLAGS) $(OBJS) $(GLFW) $(MLX42) $(LIB) -o $(NAME)
	@echo "$(G)	[$@] successfully compiled!$(NC)"

$(MLX42):
	@echo "$(NC)Compiling [MLX42 library]..."
	@if [ -d ./lib/MLX42/ ]; then \
		echo "$(G)[MLX42 library] exists!$(NC)"; \
	else \
		echo "	$(Y)Cloning [MLX42 library]$(NC)"; \
		git clone https://github.com/codam-coding-college/MLX42.git ./lib/MLX42/; \
		cd ./lib/MLX42/ && git checkout e84ea88; \
	fi
	@cd ./lib/MLX42/ && cmake -B build
	@cmake --build ./lib/MLX42/build -j4

$(LIB):
	@echo "$(NC)Compiling [libraries]..."
	@$(MAKE) -C ./lib/

$(OBJS_DIR)%.o: %.c ./include/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@ $(IS_BONUS)

clean:
	@echo "$(NC)Removing [objs]..."
	@rm -rf $(OBJS_DIR)
	@echo "$(NC)Removing [lib objs]..."
	@$(MAKE) clean -C ./lib/

fclean: clean
	@echo "$(NC)Removing [$(NAME)]..."
	@rm -rf $(NAME)
	@echo "$(NC)Removing [lib archives]..."
	@$(MAKE) fclean -C ./lib/

destroy: fclean
	@echo "$(NC)Removing [MLX42 library]..."
	@rm -rfd ./lib/MLX42/ $(MLX42)
	@echo "$(G)	[$(NAME) && MLX42] removed!$(NC)"

re: fclean all

# ------------------------------------------------------------------ TEST RULES
test:
	@./tests/tester

test_bonus:
	@./tests/tester_bonus

# ----------------------------------------------------------------------- UTILS
.PHONY: all bonus clean fclean re test

G = \033[0;32m
Y = \033[0;33m
R = \033[0;31m
NC = \033[0m
