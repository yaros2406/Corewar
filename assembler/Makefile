# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/21 15:54:57 by fwiley            #+#    #+#              #
#    Updated: 2020/06/26 09:20:44 by fwiley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		asm

CC =		gcc
FLAGS =		-Wall -Werror -Wextra $(addprefix -I , $(LIB_INC)) $(addprefix -I , $(INC))

# libft ************************************************************************
LIB_DIR =	../libft/
LIB =		$(LIB_DIR)libft.a
LIB_INC =	$(LIB_DIR)includes/

# assembler sources files ******************************************************
SRCS =		check_line.c				\
			check_tokens.c 				\
			create_binary.c				\
			error.c						\
			error_1.c					\
			error_2.c					\
			error_3.c					\
			error_print_line.c			\
			main.c						\
			parse_file.c				\
			parse_from_buff.c			\
			read_in_buff.c				\
			set_size.c					\
			staff.c						\
			struct_header.c				\
			struct_string.c				\
			struct_token.c				\
			token_create.c				\
			token_type.c
SRCS_DIR = ./srcs/

# header ***********************************************************************
INC = ../includes/

# object files *****************************************************************
OBJ_DIR = ./obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# colors ***********************************************************************
GREEN = \033[0;32m
GREEN_BOLD = \033[1;32m
RED = \033[0;31m
RED_BOLD = \033[1;31m
EOC = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INC) $(LIB_DIR)srcs/ $(LIB_DIR)includes/
	@make -C $(LIB_DIR) -s
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)
	@cp $(NAME) ../$(NAME)
	@echo "$(GREEN_BOLD)$(NAME) $(GREEN)created$(EOC)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC)
	@echo "compiling $(GREEN)$(notdir $<)$(EOC)"
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(NAME) objects files removed$(EOC)"

fclean: clean
	@rm -f $(NAME)
	@rm -f ../$(NAME)
	@echo "$(RED)Bin $(RED_BOLD)$(NAME) $(RED)removed$(EOC)"

re: fclean all
