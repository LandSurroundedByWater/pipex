# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 09:39:11 by tsaari            #+#    #+#              #
#    Updated: 2024/04/09 07:21:28 by tsaari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
#LDFLAGS = -fsanitize=address
LIBFT = -Llibft -lft
RM = rm -rf

SRCS		=	pipex.c \
				utils.c \
				utils2.c \
				parse.c \
				errorhandling.c

OBJ_DIR		= obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:		$(NAME)

$(OBJ_DIR)/%.o: %.c
			@$(CC) $(CFLAGS)  -o $@ -c $<
			@echo "\033[0;36mObject $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(LIBFT):
			@make -C "libft"

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

$(NAME):	$(LIBFT) libft/*.c $(OBJ_DIR) $(OBJS)
			@$(CC)  $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT)
			$(CC) $(CFLAGS) -I. -Ilibft $(OBJS) $(LIBFT) -o $(NAME)
			@echo "\033[1;32m\nPipex compile success!\n\033[0m"


clean:
			$(RM) $(OBJ_DIR)
			@make clean -C "libft"
			@echo "\033[0;36mClean Pipex [\033[0;32mDONE\033[0;36m]\033[0m"

fclean:		clean
			$(RM) $(NAME) $(OBJ_DIR)
			@make fclean -C "libft"
			@echo "\033[0;36mFClean Pipex [\033[0;32mDONE\033[0;36m]\033[0m"

re:			fclean all

.PHONY:		all clean fclean re