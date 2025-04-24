# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 15:44:10 by engiusep          #+#    #+#              #
#    Updated: 2025/04/24 15:08:54 by engiusep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell_prog
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADERS = lexer/lexer.h libft/libft.h parsing/parsing.h
RM = rm -f

FILES = lexer/lexer.c \
	lexer/lexer_utils.c \
	lexer/symbol.c \
	parsing/parsing_utils.c \
	parsing/parsing.c 

OBJ_DIR = obj
DIRS = $(addprefix $(OBJ_DIR)/, lexer parsing)
OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I. -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile | $(DIRS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(DIRS):
	@mkdir -p $@

clean:
	$(RM) -r $(OBJ_DIR)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: bonus all clean fclean re