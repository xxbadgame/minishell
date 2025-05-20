# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 15:44:10 by engiusep          #+#    #+#              #
#    Updated: 2025/05/20 10:01:21 by engiusep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell_prog
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
HEADERS = terminal.h \
		libft/libft.h \

RM = rm -f

FILES = terminal.c \
		lexer/lexer.c \
		lexer/symbol.c \
		parsing/handle_parsing.c \
		parsing/parsing_utils.c \
		parsing/parsing.c \
		env/env.c \
		exec/exec.c \
		exec/redirect.c \
		exec/pipeline.c \
		free/freedom.c \
		builtins/builtin_cd.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_pwd.c \
		builtins/builtin_unset.c \
		builtins/builtin_echo.c \
		builtins/builtin_export.c \
		builtins/check_builtins.c \
		builtins/builtin_print_export.c \
		builtins/builtin_export_utils.c \
		

OBJ_DIR = obj
DIRS = $(addprefix $(OBJ_DIR)/, lexer parsing env exec free builtins)
OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -I. -o $(NAME) 

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