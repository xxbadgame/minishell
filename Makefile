# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 07:58:54 by yannis            #+#    #+#              #
#    Updated: 2025/05/06 11:51:59 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = exec
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADERS = exec.h libft/libft.h
RM = rm -f

FILES = exec.c \
		exec_utils.c \
		pipeline.c \

OBJS = $(FILES:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I. -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: bonus all clean fclean re