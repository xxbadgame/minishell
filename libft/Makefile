# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 10:40:42 by yannis            #+#    #+#              #
#    Updated: 2025/06/16 12:40:58 by engiusep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_strncmp.c \
		ft_strlen.c \
		ft_split.c \
		ft_strjoin.c \
		ft_joinchar.c \
		ft_strncat.c \
		ft_strcpy.c \
		free_tab.c \
		ft_substr.c \
		ft_strndup.c \
		get_next_line/get_next_line.c \
		tab_len.c \
		ft_strchr.c	\
		ft_itoa.c \
		print_error.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_isalpha.c \
		ft_isalnum.c \
		ft_atoi.c \
		


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