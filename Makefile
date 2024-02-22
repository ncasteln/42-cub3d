# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 08:59:00 by ncasteln          #+#    #+#              #
#    Updated: 2024/02/22 01:46:21 by mrubina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Wall -Wextra #-Werror -fsanitize=thread

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
	check_valid_doors.c \
	trim_empty_lines.c

UTILS = err_free_exit.c \
	print_map.c \
	print_assets.c \
	free_utils.c \
	is_blank_line.c \
	init_structs.c \

RAYCAST = raycast.c \
	draw_wall.c \
	spritecast.c \
	sprite_init.c \
	sprite_utils.c \
	draw_door.c \
	textures.c \
	hooks.c \
	move.c \
	vectors.c \
	refine.c \

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
ifeq ($(filter randoom,$(MAKECMDGOALS)),randoom)
	IS_BONUS = -DBONUS=1
endif

# ----------------------------------------------------------------------- LEAKS
# Git repo which traces mem leaks without conflicting with MLX. Explore the
# link to know more about it and leave a star if you find useful!
LEAK_FINDER = -L./leak_finder -lft_malloc
LEAK_FINDER_INCLUDE = -I./leak_finder/includes
LEAK_FINDER_REPO = https://github.com/iwillenshofer/leak_finder.git

# ----------------------------------------------------------------------- RULES
all: $(NAME)

bonus: $(NAME)

leaks: $(NAME)_leaks

$(NAME): $(LIB) $(MLX42) $(OBJS)
	@echo "$(NC)Compiling $(NAME) executable file..."
	@$(CC) $(CFLAGS) $(OBJS) $(GLFW) $(MLX42) $(LIB) -o $(NAME)
	@echo "$(G)	[$@] successfully compiled!$(NC)"

$(NAME)_leaks: $(LIB) $(MLX42) $(OBJS) $(LEAK_FINDER)
	@echo "$(NC)Compiling $(NAME) executable file with leak checking..."
	@$(CC) $(CFLAGS) $(OBJS) $(GLFW) $(MLX42) $(LEAK_FINDER) $(LIB) -o $(NAME)
	@echo "$(G)	[$@] successfully compiled!$(NC)"

$(MLX42):
	@echo "$(NC)Getting [MLX42 library]..."
	@if [ -d ./lib/MLX42/ ]; then \
		echo "$(G)[MLX42 library] already exists!$(NC)"; \
	else \
		echo "	$(Y)Cloning [MLX42 library]$(NC)"; \
		git clone https://github.com/codam-coding-college/MLX42.git ./lib/MLX42/; \
		cd ./lib/MLX42/ && git checkout e84ea88; \
	fi
	@echo "$(NC)Compiling [MLX42 library]..."
	@cd ./lib/MLX42/ && cmake -B build
	@cmake --build ./lib/MLX42/build -j4

$(LEAK_FINDER):
	@echo "$(NC)Getting [leak_finder]...(visit $(G)$(LEAK_FINDER_REPO) $(NC)and leave a star!)"
	@if [ -d ./leak_finder/ ]; then \
		echo "$(G)[leak_finder] already exists!$(NC)"; \
	else \
		echo "	$(Y)Cloning [leak_finder library]$(NC)"; \
		git clone $(LEAK_FINDER_REPO) leak_finder; \
	fi
	@echo "$(NC)Compiling [leak_finder]..."
	@$(MAKE) -C ./leak_finder
	@cp ./leak_finder/libft_malloc.so ./
	@cp ./leak_finder/libft_malloc_x86_64_Darwin.so ./
	@echo "$(Y)To use leak_finder: include 'malloc.h' on the top of your header and use \
	the appropriate function print_leaks() at the exit points.$(NC)"

$(LIB):
	@echo "$(NC)Compiling [libraries]..."
	@$(MAKE) -C ./lib/

$(OBJS_DIR)%.o: %.c ./include/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@$(CC) -c $(CFLAGS) $< $(INCLUDE) $(LEAK_FINDER_INCLUDE) -o $@ $(IS_BONUS)

# ----------------------------------------------------------------- CLEAN RULES
clean:
	@echo "$(NC)Removing [objs]..."
	@rm -rf $(OBJS_DIR)
	@echo "$(NC)Removing [lib objs]..."
	@$(MAKE) clean -C ./lib/

fclean: clean
	@echo "$(NC)Removing [$(NAME)]..."
	@rm -rf $(NAME) $(NAME)_leaks
	@echo "$(NC)Removing [lib archives]..."
	@$(MAKE) fclean -C ./lib/

re: fclean all

clean_mlx:
	@echo "$(NC)Removing [MLX42 library]..."
	@rm -rfd ./lib/MLX42/ $(MLX42)

clean_leak_finder:
	@echo "$(NC)Removing [leak_finder]..."
	@rm -rfd *.so
	@rm -rfd ./leak_finder/

destroy: fclean clean_mlx clean_leak_finder
	@rm -rf ./tests/randoom.cub

# ------------------------------------------------------------------ TEST RULES
test: fclean all
	@./tests/tester.sh

test_bonus: fclean bonus
	@./tests/tester_bonus.sh

# --------------------------------------------------------------------- RANDOOM
randoom: bonus
	@echo "$(R)"
	@echo "______  ___   _   _______ _____  ________  ___"
	@echo "| ___ \/ _ \ | \ | |  _  \  _  ||  _  |  \/  |"
	@echo "| |_/ / /_\ \|  \| | | | | | | || | | | .  . |"
	@echo "|    /|  _  || . ' | | | | | | || | | | |\/| |"
	@echo "| |\ \| | | || |\  | |/ /\ \_/ /\ \_/ / |  | |"
	@echo "\_| \_\_| |_/\_| \_/___/  \___/  \___/\_|  |_/"
	@echo "$(NC)"
	@ rm -rfd ./tests/randoom.cub
	@./tests/randoom.sh
	@./cub3D ./tests/randoom.cub

# ----------------------------------------------------------------------- UTILS
.PHONY: all bonus clean fclean re test leaks clean_mlx clean_leak_finder destroy randoom

G = \033[0;32m
Y = \033[0;33m
R = \033[0;31m
NC = \033[0m
