/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 19:14:21 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/25 20:02:17 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void			write_byte(t_game *game, t_uint32 position, t_int32 value,
				t_uint32 id)
{
	t_uint32	unsigned_value;
	t_uint8		byte;
	t_uint8		i;

	if (!game)
		return ;
	unsigned_value = (t_uint32)value;
	i = 0;
	while (i < REG_SIZE)
	{
		byte = (t_uint8)((unsigned_value >> ((3 - i) * 8)) & 0xff);
		game->map[crop_index_u(position + i)] = byte;
		if (game->flags & VISUAL)
		{
			game->map_vs[crop_index_u(position + i)].value = byte;
			game->map_vs[crop_index_u(position + i)].id = id;
		}
		i++;
	}
}

static void		print_st(t_process process, t_game game)
{
	print_op(process);
	ft_printf("r%d %d\n", read_arg(process, game, 0),
		read_arg(process, game, 1));
}

void			op_st(t_process *process, t_game *game)
{
	t_int32		reg_value;
	t_uint8		reg_index;
	t_uint8		dst_type;
	t_int32		address;

	if (!process || !game)
		return ;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_st(*process, *game);
	reg_value = get_value_arg(*process, *game, 0, TRUE);
	dst_type = get_type_arg(*process, *game, 1);
	if (dst_type == T_IND)
	{
		address = (t_int32)read_arg(*process, *game, 1) % IDX_MOD
				+ process->pos;
		address = crop_index(address);
		write_byte(game, address, reg_value, process->player_id);
	}
	else if (dst_type == T_REG)
	{
		reg_index = read_arg(*process, *game, 1);
		process->reg[reg_index] = reg_value;
	}
}

static void		print_sti(t_process process, t_game game)
{
	t_int32		reg_index;
	t_int32		arg_2;
	t_int32		arg_3;
	t_uint32	address;

	reg_index = read_arg(process, game, 0);
	arg_2 = get_value_arg(process, game, 1, TRUE);
	arg_3 = get_value_arg(process, game, 2, TRUE);
	address = (arg_2 + arg_3) % IDX_MOD + process.pos;
	print_op(process);
	ft_printf("r%d %d %d\n", reg_index, arg_2, arg_3);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			arg_2, arg_3, arg_2 + arg_3, address);
}

void			op_sti(t_process *process, t_game *game)
{
	t_int32		reg_value;
	t_int32		address;

	if (!process || !game)
		return ;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
		print_sti(*process, *game);
	reg_value = get_value_arg(*process, *game, 0, TRUE);
	address = get_value_arg(*process, *game, 1, TRUE)
			+ get_value_arg(*process, *game, 2, TRUE);
	address = crop_index_u((t_uint32)(address % IDX_MOD) + process->pos);
	write_byte(game, address, reg_value, process->player_id);
}
