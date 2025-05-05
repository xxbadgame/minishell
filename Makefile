# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 15:44:10 by engiusep          #+#    #+#              #
#    Updated: 2025/05/05 10:09:53 by ynzue-es         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell_prog
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADERS = terminal.h \
		lexer/lexer.h \
		libft/libft.h \
		parsing/parsing.h \
		env/env.h \

RM = rm -f

FILES = terminal.c \
	lexer/lexer.c \
	lexer/lexer_utils.c \
	lexer/symbol.c \
	parsing/parsing_utils.c \
	parsing/parsing.c \
	env/env.c \
	env/env_path.c \
	env/env_edit.c \

OBJ_DIR = obj
DIRS = $(addprefix $(OBJ_DIR)/, lexer parsing env)
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