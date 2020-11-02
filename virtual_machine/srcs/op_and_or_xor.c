/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 10:27:17 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/06 11:38:21 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void			op_and(t_process *process, t_game *game)
{
	t_uint8		reg_index;
	t_uint32	lft;
	t_uint32	rft;
	t_int32		value;

	if (!process || !game)
		return ;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_load_op(*process, *game);
	lft = (t_uint32)get_value_arg(*process, *game, 0, TRUE);
	rft = (t_uint32)get_value_arg(*process, *game, 1, TRUE);
	value = (t_int32)(lft & rft);
	reg_index = read_arg(*process, *game, 2);
	process->reg[reg_index] = value;
	process->carry = (value == 0) ? 1 : 0;
}

void			op_or(t_process *process, t_game *game)
{
	t_uint8		reg_index;
	t_uint32	lft;
	t_uint32	rft;
	t_int32		value;

	if (!process || !game)
		return ;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_load_op(*process, *game);
	lft = (t_uint32)get_value_arg(*process, *game, 0, TRUE);
	rft = (t_uint32)get_value_arg(*process, *game, 1, TRUE);
	value = (t_int32)(lft | rft);
	reg_index = read_arg(*process, *game, 2);
	process->reg[reg_index] = value;
	process->carry = (value == 0) ? 1 : 0;
}

void			op_xor(t_process *process, t_game *game)
{
	t_uint8		reg_index;
	t_uint32	lft;
	t_uint32	rft;
	t_int32		value;

	if (!process || !game)
		return ;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_load_op(*process, *game);
	lft = (t_uint32)get_value_arg(*process, *game, 0, TRUE);
	rft = (t_uint32)get_value_arg(*process, *game, 1, TRUE);
	value = (t_int32)(lft ^ rft);
	reg_index = read_arg(*process, *game, 2);
	process->reg[reg_index] = value;
	process->carry = (value == 0) ? 1 : 0;
}
