/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:08:11 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/25 17:37:53 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

static void		print_reg_op(t_process process, t_game game)
{
	print_op(process);
	ft_printf("r%d r%d r%d\n", read_arg(process, game, 0),
		read_arg(process, game, 1), read_arg(process, game, 2));
}

void			op_add(t_process *process, t_game *game)
{
	t_int32		reg_index;
	t_int32		reg_sum;

	if (!process || !game)
		return ;
	reg_sum = get_value_arg(*process, *game, 0, TRUE)
			+ get_value_arg(*process, *game, 1, TRUE);
	reg_index = read_arg(*process, *game, 2);
	process->reg[reg_index] = reg_sum;
	process->carry = (reg_sum == 0) ? 1 : 0;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_reg_op(*process, *game);
}

void			op_sub(t_process *process, t_game *game)
{
	t_int32		reg_index;
	t_int32		reg_sub;

	if (!process || !game)
		return ;
	reg_sub = get_value_arg(*process, *game, 0, TRUE)
			- get_value_arg(*process, *game, 1, TRUE);
	reg_index = read_arg(*process, *game, 2);
	process->reg[reg_index] = reg_sub;
	process->carry = (reg_sub == 0) ? 1 : 0;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_reg_op(*process, *game);
}
