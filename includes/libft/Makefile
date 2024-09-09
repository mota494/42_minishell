NAME = libft.a
CC= gcc
FLAGS= -Wall -Wextra -Werror
SRC= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_toupper.c ft_tolower.c
BSRC = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lslast.c  ft_lstnew.c ft_lstsize.c
RM = rm -rf
OBJS=$(SRC:.c=.o)
BOBJS=$(BSRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $*.c -o $*.o

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean:
	$(RM) $(OBJS) $(BOBJS) libft.a

re: fclean all

exec:
	cc -w main.c $(SRC)

bonus: $(OBJS) $(BOBJS)
	ar rc $(NAME) $(OBJS) $(BOBJS)
