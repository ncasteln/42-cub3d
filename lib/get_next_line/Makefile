# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 09:08:19 by ncasteln          #+#    #+#              #
#    Updated: 2023/12/18 10:56:47 by ncasteln         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line.c \
	get_next_line_utils.c
SRC_BONUS = get_next_line_bonus.c \
	get_next_line_utils_bonus.c
OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))
# OBJS = $(addprefix $(OBJS_DIR), $(SRC_BONUS:.c=.o))
OBJS_FLAG = $(OBJS_DIR).mand_flag
ifneq ($(filter bonus,$(MAKECMDGOALS)),)
	OBJS = $(addprefix $(OBJS_DIR), $(SRC_BONUS:.c=.o))
	OBJS_FLAG = $(OBJS_DIR).bonus_flag
endif
HEADER = ./get_next_line.h

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS) $(OBJS_FLAG)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)	$(NAME) successfully created!$(NC)"

$(OBJS_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./

$(OBJS_FLAG):
	@rm -rf $(OBJS_DIR).mand_flag
	@rm -rf $(OBJS_DIR).bonus_flag
	@mkdir -p $(OBJS_DIR)
	@touch $(OBJS_FLAG)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)	$(NAME) objs successfully removed!$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)	$(NAME) successfully removed!$(NC)"

re: fclean all

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

.PHONY: all, clean, fclean, re
