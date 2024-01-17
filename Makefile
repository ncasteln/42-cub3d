# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 08:59:00 by ncasteln          #+#    #+#              #
#    Updated: 2024/01/17 10:47:07 by ncasteln         ###   ########.fr        #
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
	./src/minimap_bonus/ \

PARSER = parse.c \
	parse_file_content.c \
	parse_type_id.c \
	extract_type_id_value.c \
	parse_map.c \
	parse_player.c \
	path_validation.c \
	parser_utils_0.c \
	parser_utils_1.c \

UTILS = err_free_exit.c \
	print_map.c \
	print_assets.c \
	free_utils.c

RAYCAST = raycast.c \
	hooks.c \
	utils.c \
	move.c \

MINIMAP = draw_minimap_bonus.c

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
# OBJS_FLAG = $(OBJS_DIR).mandatory_flag
# OBJS_FLAG = $(OBJS_DIR).bonus_flag
# OBJS = $(addprefix $(OBJS_DIR), $(SRC_BONUS:.c=.o))

# ----------------------------------------------------------------- BASIC RULES
all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIB) $(MLX42) $(OBJS) #$(OBJS_FLAG)
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
	fi
	@cd ./lib/MLX42/ && cmake -B build
	@cmake --build ./lib/MLX42/build -j4

$(LIB):
	@echo "$(NC)Compiling [libraries]..."
	@$(MAKE) -C ./lib/

$(OBJS_DIR)%.o: %.c ./include/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@ $(IS_BONUS)

# [objs_flag] make possible to re-make the exe file alternately between
# 'all' and 'bonus' rule, without clean or fclean them
# $(OBJS_FLAG):
# 	@rm -rf $(OBJS_DIR).mandatory_flag
# 	@rm -rf $(OBJS_DIR).bonus_flag
# 	@mkdir -p $(OBJS_DIR)
# 	@touch $(OBJS_FLAG)
# 	@echo "$(Y)	Created [$(OBJS_FLAG)]"

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

test: $(NAME)
	@./tests/tester

re: fclean all

# --------------------------------------------------------------- SPECIAL RULES
# update:
#  	git submodule update --remote MLX42

# ----------------------------------------------------------------------- UTILS
.PHONY: all bonus clean fclean re

G = \033[0;32m
Y = \033[0;33m
R = \033[0;31m
NC = \033[0m
