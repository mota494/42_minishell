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
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -fr

#PATHS
INC =  -I inc
LIBFT = includes/libft/libft.a
FPRINTF = includes/ft_fprintf/libftprintf.a
SRCD = src/
OBJD = obj/

#FILES
SRCS = $(SRCD)000_utils2.c $(SRCD)000_utils3.c $(SRCD)000_utils4.c $(SRCD)000_utils5.c $(SRCD)000_utils6.c $(SRCD)000_utils.c $(SRCD)100_free.c $(SRCD)100_main.c $(SRCD)105_env.c $(SRCD)105_env_utils.c $(SRCD)405_parse_line.c $(SRCD)200_check_syntax.c $(SRCD)200_syntax_utils.c $(SRCD)205_operators_check2.c $(SRCD)205_operators_check.c $(SRCD)210_syntax_error.c $(SRCD)300_get_line.c $(SRCD)300_get_line_utils.c $(SRCD)305_define_type.c $(SRCD)305_define_type_utils.c $(SRCD)400_parser.c $(SRCD)405_parser_get_replace_var.c $(SRCD)405_parser_vars_dollar.c $(SRCD)410_parser_special.c $(SRCD)410_parser_tilde.c $(SRCD)415_parser_heredoc.c $(SRCD)500_execution.c $(SRCD)510_redirects_utils.c $(SRCD)500_execution_run.c $(SRCD)505_exec_utils.c $(SRCD)510_redirect_and_wait.c $(SRCD)510_redirects.c $(SRCD)600_cd.c $(SRCD)600_echo.c $(SRCD)600_env_builtin.c $(SRCD)600_exit.c $(SRCD)600_pwd.c $(SRCD)600_unset.c $(SRCD)610_export.c $(SRCD)610_export_print.c $(SRCD)610_export_vars.c $(SRCD)700_signals.c 

OBJS = $(patsubst $(SRCD)%.c, $(OBJD)%.o, $(SRCS))
$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

#RULES
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FPRINTF)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(FPRINTF) -lreadline -lncurses -o $(NAME)
	echo "$(GREEN)All files compiled!$(RESET)"

$(LIBFT):
	make -s -C includes/libft
	make bonus -s -C includes/libft

$(FPRINTF):
	make -s -C includes/ft_fprintf
	
valgrind:
	@make re
	@valgrind --leak-check=full --suppressions=readline_leaks --show-leak-kinds=all --track-origins=yes --tool=memcheck ./minishell
	#@valgrind --leak-check=full --suppressions=readline_leaks --show-leak-kinds=all --track-origins=yes --tool=memcheck  --log-file="valgrind_leaks.txt" ./minishell

clean:
	$(RM) $(OBJS)
	make -s -C includes/libft clean
	make -s -C includes/ft_fprintf clean

fclean: clean
	$(RM) $(NAME)
	make -s -C includes/libft fclean
	make -s -C includes/ft_fprintf fclean
	echo "$(RED)Deleted: $(RESET) $(GREEN)$(NAME)$(RESET)"

re: fclean all

set: $(OBJS) $(LIBFT)
	$(CC) $(INC) $(OBJS) $(LIBFT) -lreadline -lncurses -o $(NAME)

norm:
	norminette $(SRCS) minishell.h inc.h

gdb: $(OBJS) $(LIBFT)
	@make re
	gdb -tui minishell
	

.PHONY: all clean fclean re

.SILENT:
