# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuor <skuor@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 16:18:45 by skuor             #+#    #+#              #
#    Updated: 2025/10/05 16:54:35 by skuor            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 
MAKE = make
CFLAGS = -Wall -Wextra -Werror -g3
SRC_DIR = ./src/
OBJ_DIR = ./objects/
INC_DIR = ./includes/
BLTINS_DIR = $(SRC_DIR)builtins/
UTILS_DIR = $(SRC_DIR)utils/
LIBFT_DIR = ./libft/

SRC_FILES = main.c ft_tokenisation.c variables.c environ.c environ2.c fields_splitting.c \
			ft_type_token.c external_cmd.c exec.c expansion.c ft_heredoc.c ft_signals.c \
			error_msg.c error_msg2.c

BLTINS_FILES = ft_exit.c ft_pwd.c ft_env.c ft_echo.c ft_cd.c ft_unset.c ft_export.c

UTILS_FILES = utils.c utils_expan.c utils_tokens.c ft_type_token_utils.c \
			  utils_builtins.c utils_cmd.c utils_quotes.c utils_var.c \
			  free.c clean.c ft_utils_exect_redirections.c ft_utils_tests.c \
			  init.c

OBJ = 	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(BLTINS_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(UTILS_FILES:.c=.o))

INC_H = -I $(INC_DIR) -I $(LIBFT_DIR)/includes/

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INC_H) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
#	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

$(OBJ_DIR)%.o: $(BLTINS_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean clean all

.PHONY: all clean fclean re
	