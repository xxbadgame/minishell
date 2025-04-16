# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 15:44:10 by engiusep          #+#    #+#              #
#    Updated: 2025/04/16 16:05:05 by engiusep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADERS = lexer.h libft/libft.h
RM = rm -f

FILES = lexer.c \
		lexer_utils.c \
		symbol.c

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