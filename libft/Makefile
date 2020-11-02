# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frenna <frenna@student42.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 10:35:56 by Elena             #+#    #+#              #
#    Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

INCLUDES = ./includes/

SRC_NAMES = calc_double.c \
	ch_transform.c \
	ft_atoi.c \
	ft_buffer.c \
	ft_bzero.c \
	ft_isdigit.c \
	ft_isspace.c \
	ft_isnegative.c \
	ft_itoa_base.c \
	ft_itoa_pf.c \
	ft_ldtoa_pf.c \
	ft_memalloc.c \
	ft_memchr.c \
	ft_memset.c \
	ft_parse.c \
	ft_power.c \
	ft_printf.c \
	ft_putchar.c \
	ft_putnchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putstr.c \
	ft_putstr_free.c \
	ft_putstr_fd.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strncpy.c \
	ft_utoa_pf.c \
	is_valid.c \
	num_transform.c \
	p_transform.c \
	parse.c \

SRCS_PATH = srcs/
OBJ_PATH  = obj/

SRCS = $(addprefix $(SRCS_PATH), $(SRC_NAMES))
OBJ = $(addprefix $(OBJ_PATH), $(SRC_NAMES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[32mLibrary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJ): $(INCLUDES)libft.h $(SRCS)
	@mkdir -p obj
	@gcc -c $(FLAGS) -I $(INCLUDES) $(SRCS)
	@echo "\033[34m\033[1mCompilation of Libft \033[0m\033[36mobject files \033[1m\033[34m done.\033[0m"
	@mv $(SRC_NAMES:.c=.o) $(OBJ_PATH)

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[31mLibft objects files\033[1;31m\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
