# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frenna <frenna@student42.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 13:19:19 by frenna            #+#    #+#              #
#    Updated: 2020/06/23 16:40:57 by fwiley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = project

LIBFT_DIR = ./libft/
ASM_DIR = ./assembler/
VM_DIR = ./virtual_machine/

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_DIR) -s
	@make -C $(VM_DIR) -s
	@make -C $(ASM_DIR) -s

clean:
	@make clean -C $(LIBFT_DIR) -s
	@make clean -C $(VM_DIR) -s
	@make clean -C $(ASM_DIR) -s

fclean:
	@make fclean -C $(LIBFT_DIR) -s
	@make fclean -C $(VM_DIR) -s
	@make fclean -C $(ASM_DIR) -s

re: fclean all
