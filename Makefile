# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 15:44:10 by engiusep          #+#    #+#              #
#    Updated: 2025/07/03 11:55:04 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADERS = terminal.h \
		libft/libft.h \

RM = rm -f

FILES = terminal.c \
		terminal_utils.c \
		lexer/lexer.c \
		lexer/lexer_utils.c \
		lexer/lexer_utils2.c  \
		lexer/quote_utils.c \
		lexer/quote_utils2.c \
		lexer/quote_utils3.c \
		lexer/quote_utils4.c \
		lexer/symbol.c \
		parsing/handle_parsing.c \
		parsing/token_checker.c \
		parsing/token_checker_utils.c \
		parsing/parsing.c \
		env/env.c \
		exec/exec.c \
		exec/exec_utils.c \
		exec/exec_utils2.c \
		exec/redirect.c \
		exec/redirect_utils.c \
		exec/redirect_utils2.c \
		exec/redirect_utils3.c \
		exec/pipeline.c \
		exec/pipeline_utils.c \
		exec/pipeline_utils2.c \
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
		signal/signal_handle.c\
		
OBJ_DIR = obj
DIRS = $(addprefix $(OBJ_DIR)/, lexer parsing env exec free builtins signal)
OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
LIBFT = libft/libft.a

LIBFT_SRC = libft/ft_strncmp.c \
			libft/ft_strlen.c \
			libft/ft_split.c \
			libft/ft_strjoin.c \
			libft/ft_joinchar.c \
			libft/ft_strncat.c \
			libft/ft_strcpy.c \
			libft/free_tab.c \
			libft/ft_substr.c \
			libft/ft_strndup.c \
			libft/get_next_line/get_next_line.c \
			libft/tab_len.c \
			libft/ft_strchr.c	\
			libft/ft_itoa.c \
			libft/print_error.c \
			libft/ft_putendl_fd.c \
			libft/ft_putstr_fd.c \
			libft/ft_isalpha.c \
			libft/ft_isnum.c \
			libft/ft_atoi.c \
			libft/ft_isalnum.c \

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -I. -o $(NAME) 

$(LIBFT): $(LIBFT_SRC)
	make -C libft

$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile | $(DIRS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	
$(DIRS):
	@mkdir -p $@

-include $(OBJS:.o=.d)

clean:
	$(RM) -r $(OBJ_DIR)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: bonus all clean fclean re