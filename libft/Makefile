# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuor <skuor@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 10:10:18 by skuor             #+#    #+#              #
#    Updated: 2025/08/12 18:58:58 by skuor            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = ./srcs/
INC_DIR = ./includes/
OBJ_DIR = ./objects/

CHECKS_DIR = $(addprefix $(SRC_DIR), checks/)
CONVERSION_DIR = $(addprefix $(SRC_DIR), conversion/)
DISPLAY_DIR = $(addprefix $(SRC_DIR), display/)
LINKED_LIST_DIR = $(addprefix $(SRC_DIR), linked_list/)
MEMORY_DIR = $(addprefix $(SRC_DIR), memory/)
STRINGS_DIR = $(addprefix $(SRC_DIR), strings/)

CHECKS_FILES =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c is_sign.c ft_isspace.c

CONVERSION_FILES = ft_toupper.c ft_tolower.c ft_atoi.c ft_itoa.c ft_atol.c

DISPLAY_FILES = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_printf.c ft_hexadecimal.c ft_hexaptr.c ft_putchar.c ft_putstr.c \
				ft_putnbr.c ft_putnbr_u.c ft_print_array.c

LINKED_LIST_FILES = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
					ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

MEMORY_FILES =	ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_calloc.c \
				ft_free_array_str.c

STRINGS_FILES =	ft_split.c ft_striteri.c ft_strlcpy.c ft_strncmp.c ft_strtrim.c \
				ft_strchr.c ft_strjoin.c ft_strlen.c ft_strnstr.c ft_substr.c \
				ft_strdup.c ft_strlcat.c ft_strmapi.c ft_strrchr.c get_next_line.c \
				ft_array_dup.c ft_strjoin_free.c \


OBJ = $(addprefix $(OBJ_DIR), $(CHECKS_FILES:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(CONVERSION_FILES:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(DISPLAY_FILES:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(LINKED_LIST_FILES:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(MEMORY_FILES:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(STRINGS_FILES:.c=.o)) 
	  
CC = cc
CFLAGS = -Wall -Wextra -Werror 
AR = ar -rcs
INC_H = -I $(INC_DIR)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(CHECKS_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(CONVERSION_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(DISPLAY_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(LINKED_LIST_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(MEMORY_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(STRINGS_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
