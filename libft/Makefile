NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_strncmp.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strncat.c \
		ft_strlcpy.c \
		ft_substr.c \
		get_next_line/get_next_line.c \


OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re