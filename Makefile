# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuor <skuor@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 16:18:45 by skuor             #+#    #+#              #
#    Updated: 2025/07/08 17:50:15 by skuor            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 
MAKE = make
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src/
OBJ_DIR = ./objects/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRC_FILES = main.c 

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

INC_H = -I $(INC_DIR) -I $(LIBFT_DIR)/includes/

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INC_H) -lreadline $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean clean all

.PHONY: all clean fclean re
	