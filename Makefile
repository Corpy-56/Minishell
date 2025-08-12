# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuor <skuor@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 16:18:45 by skuor             #+#    #+#              #
#    Updated: 2025/08/12 15:37:18 by skuor            ###   ########.fr        #
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

SRC_FILES = main.c ft_tokenisation.c variables.c
BLTINS_FILES = ft_exit.c ft_pwd.c ft_env.c ft_echo.c ft_cd.c ft_unset.c ft_export.c
UTILS_FILES = utils.c var_utils.c

OBJ = 	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(BLTINS_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(UTILS_FILES:.c=.o)) \

INC_H = -I $(INC_DIR) -I $(LIBFT_DIR)/includes/

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INC_H) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
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
	