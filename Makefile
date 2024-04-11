# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 09:39:11 by tsaari            #+#    #+#              #
#    Updated: 2024/04/10 10:53:43 by tsaari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

SRCS = pipex.c utils.c utils2.c parse.c errorhandling.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = obj

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;36mObject $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) -I. -Ilibft $(OBJS) $(LIBFT) -o $(NAME)
	@echo "\033[1;32mLibft library ready!\n\033[0m"
	@echo "\033[1;32mPipex compile success!\n\033[0m"

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C libft
	@echo "\033[0;36mClean Pipex [\033[0;32mDONE\033[0;36m]\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@echo "\033[0;36mFClean Pipex [\033[0;32mDONE\033[0;36m]\033[0m"

re: fclean all

.PHONY: all clean fclean re
