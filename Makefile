NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf


LIBFT= 	libft/libft.a

SRCS		= pipex.c \
				utils.c

OBJ_DIR		= obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:		$(NAME)


$(OBJ_DIR)/%.o: %.c
			@$(CC) $(CFLAGS)  -o $@ -c $<
			@echo "\033[0;36mObject $@ [\033[0;32mOK\033[0;36m]\033[0m"

$(LIBFT):
			@make -C "libft"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJ_DIR) $(OBJS) $(LIBFT) libft/*.c
			@$(CC) $(OBJS)  $(LIBFT) -o $(NAME)
			@echo "\033[1;32mPipex compile success!\n\033[0m"


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