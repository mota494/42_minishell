#COLORS
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
MAGENTA	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

#PROGRAM NAME | COMPILER | FLAGS 
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -fr

#PATHS
INC =  -I inc
LIBFT = includes/libft/libft.a
SRCD = src/
OBJD = obj/

#FILES
SRCS = $(SRCD)parser.c $(SRCD)define_type.c $(SRCD)main.c $(SRCD)utils.c  $(SRCD)utils2.c $(SRCD)get_line.c $(SRCD)get_line_utils.c

OBJS = $(patsubst $(SRCD)%.c, $(OBJD)%.o, $(SRCS))
$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

#RULES
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(INC) $(OBJS) $(LIBFT) -o $(NAME)
	echo "$(GREEN)All files compiled!$(RESET)"

$(LIBFT):
	make -s -C includes/libft
	make bonus -s -C includes/libft

valgrind:
	@make re
	@valgrind --leak-check=full --suppressions=readline_leaks --show-leak-kinds=all --track-origins=yes --tool=memcheck ./minishell

clean:
	$(RM) $(OBJS)
	make -s -C includes/libft clean

fclean: clean
	$(RM) $(NAME)
	make -s -C includes/libft fclean
	echo "$(RED)Deleted: $(RESET) $(GREEN)$(NAME)$(RESET)"

re: fclean all

norm:
	norminette $(SRCS) minishell.h inc.h

.PHONY: all clean fclean re

.SILENT:
