/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld_ldi_lld_lldi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 14:01:21 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 15:31:40 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void			op_ld(t_process *process, t_game *game)
{
	t_uint8		reg_index;
	t_int32		value;

	if (!process || !game)
		return ;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_load_op(*process, *game);
	value = get_value_arg(*process, *game, 0, TRUE);
	reg_index = read_arg(*process, *game, 1);
	process->reg[reg_index] = value;
	process->carry = (value == 0) ? 1 : 0;
}

void			op_ldi(t_process *process, t_game *game)
{
	t_uint8		reg_index;
	t_int32		arg_one_address;
	t_int32		arg_two_address;
	t_int32		address;
	t_int32		value;

	if (!process || !game)
		return ;
	arg_one_address = get_value_arg(*process, *game, 0, TRUE);
	arg_two_address = get_value_arg(*process, *game, 1, TRUE);
	address = (arg_one_address + arg_two_address) % IDX_MOD + process->pos;
	address = crop_index(address);
	reg_index = read_arg(*process, *game, 2);
	value = read_byte(game->map, (t_uint32)address, REG_SIZE);
	process->reg[reg_index] = value;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
	{
		print_load_op(*process, *game);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			arg_one_address, arg_two_address, arg_one_address + arg_two_address,
			(arg_one_address + arg_two_address) % IDX_MOD + process->pos);
	}
}

void			op_lld(t_process *process, t_game *game)
{
	t_uint8		reg_index;
	t_int32		value;

	if (!process || !game)
		return ;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_load_op(*process, *game);
	value = get_value_arg(*process, *game, 0, FALSE);
	reg_index = read_arg(*process, *game, 1);
	process->reg[reg_index] = value;
	process->carry = (value == 0) ? 1 : 0;
}

void			op_lldi(t_process *process, t_game *game)
{
	t_uint8		reg_index;
	t_int32		arg_one_address;
	t_int32		arg_two_address;
	t_int32		address;
	t_int32		value;

	if (!process || !game)
		return ;
	arg_one_address = get_value_arg(*process, *game, 0, TRUE);
	arg_two_address = get_value_arg(*process, *game, 1, TRUE);
	address = (arg_one_address + arg_two_address) + process->pos;
	address = crop_index(address);
	reg_index = read_arg(*process, *game, 2);
	value = read_byte(game->map, (t_uint32)address, REG_SIZE);
	process->reg[reg_index] = value;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
	{
		print_load_op(*process, *game);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			arg_one_address, arg_two_address, arg_one_address + arg_two_address,
			arg_one_address + arg_two_address + process->pos);
	}
	process->carry = (value == 0) ? 1 : 0;
}
