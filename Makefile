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
<<<<<<< HEAD
SRCS =	$(SRCD)000_utils.c $(SRCD)001_utils2.c $(SRCD)002_utils3.c $(SRCD)100_main.c $(SRCD)101_parser.c $(SRCD)200_get_line.c $(SRCD)201_get_line_utils.c $(SRCD)203_define_type.c $(SRCD)204_define_type_utils.c $(SRCD)300_check_syntax.c $(SRCD)301_operators_check2.c $(SRCD)301_operators_check.c $(SRCD)302_syntax_error.c $(SRCD)303_syntax_utils.c $(SRCD)400_runtime.c $(SRCD)401_exit.c $(SRCD)402_echo.c $(SRCD)403_pwd.c $(SRCD)404_cd.c\
		$(SRCD)500_execution.c $(SRCD)501_redirect_and_wait.c $(SRCD)101_parser_special.c
=======
SRCS =	$(SRCD)000_utils.c $(SRCD)001_utils2.c $(SRCD)002_utils3.c $(SRCD)100_main.c $(SRCD)101_parser.c $(SRCD)101_parser_special.c $(SRCD)101_parser_tilde.c $(SRCD)200_get_line.c $(SRCD)201_get_line_utils.c $(SRCD)203_define_type.c $(SRCD)204_define_type_utils.c $(SRCD)300_check_syntax.c $(SRCD)301_operators_check2.c $(SRCD)301_operators_check.c $(SRCD)302_syntax_error.c $(SRCD)303_syntax_utils.c $(SRCD)400_runtime.c $(SRCD)401_exit.c $(SRCD)402_echo.c $(SRCD)403_pwd.c $(SRCD)404_cd.c $(SRCD)500_execution.c $(SRCD)501_redirect_and_wait.c $(SRCD)502_run_cmdx.c $(SRCD)101_parser_vars.c
>>>>>>> a613dda4123f9f1c6f7ca1dc7d2d72b654293deb

OBJS = $(patsubst $(SRCD)%.c, $(OBJD)%.o, $(SRCS))
$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

#RULES
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) -lreadline -lncurses -o $(NAME)
	echo "$(GREEN)All files compiled!$(RESET)"

$(LIBFT):
	make -s -C includes/libft
	make bonus -s -C includes/libft

valgrind:
	@make re
	@valgrind --leak-check=full --suppressions=readline_leaks --show-leak-kinds=all --track-origins=yes --tool=memcheck  --log-file="valgrind_leaks.txt" ./minishell

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
