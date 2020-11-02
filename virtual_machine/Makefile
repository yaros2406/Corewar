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

NAME =		corewar

CC =		gcc
FLAGS =		-Wall -Werror -Wextra $(addprefix -I , $(LIB_INC)) $(addprefix -I , $(INC))

# libft ************************************************************************
LIB_DIR =	../libft/
LIB =		$(LIB_DIR)libft.a
LIB_INC =	$(LIB_DIR)includes/

# virtual machine sources files ************************************************
SRCS =		arg_op.c					\
			check_op.c					\
			check_process.c				\
			execute_op.c				\
			main.c						\
			parse_args.c				\
			parse_file.c				\
			parse_flags.c				\
			print_basic.c				\
			print_debug.c				\
			put_error.c					\
			run_game.c					\
			run_visual.c				\
			staff.c						\
			struct_game.c				\
			struct_player.c				\
			struct_process.c			\
			struct_process_indexation.c	\
			vs_config.c					\
			vs_print.c					\
			vs_print_info.c				\
			op_add_sub.c				\
			op_aff.c					\
			op_and_or_xor.c				\
			op_fork_lfork.c				\
			op_ld_ldi_lld_lldi.c		\
			op_live.c					\
			op_st_sti.c					\
			op_zjmp.c
SRCS_DIR =	./srcs/

# header ***********************************************************************
INC =		../includes/

# object files *****************************************************************
OBJ_DIR =	./obj/
OBJ =		$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# colors ***********************************************************************
GREEN = \033[0;32m
GREEN_BOLD = \033[1;32m
RED = \033[0;31m
RED_BOLD = \033[1;31m
EOC = \033[0m

#$(TARGET_DIR) = ../

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INC) $(LIB_DIR)srcs/ $(LIB_DIR)includes/
	@make -C $(LIB_DIR) -s
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -lncurses -o $(NAME)
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
