/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 09:49:38 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 16:04:25 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_op.h"
#include "op_tab.h"

void				print_next_position(t_process process, t_game game)
{
	t_uint32		len;
	t_uint32		i;

	if (!(game.flags & DEBUG) || !(game.debug_nbr & DEBUG_PC))
		return ;
	if (process.op_code == 9 && process.carry)
		return ;
	if (process.next_pos < process.pos)
		len = process.next_pos + MEM_SIZE - process.pos;
	else
		len = process.next_pos - process.pos;
	ft_printf("ADV %u (0x%04x -> 0x%04x) ", len, process.pos,
		process.pos + len);
	i = 0;
	while (i < len)
	{
		ft_printf("%02x ", game.map[crop_index_u(process.pos + i)]);
		i++;
	}
	ft_printf("\n");
}

void				print_op(t_process process)
{
	ft_printf("P%5u | %s ", process.id, g_op_tab[process.op_code].name);
}

void				print_load_op(t_process process, t_game game)
{
	t_op			op;
	t_int32			i;

	print_op(process);
	op = g_op_tab[process.op_code];
	i = 0;
	while (i < op.arg_num - 1)
	{
		ft_printf("%d ", get_value_arg(process, game, (size_t)i, TRUE));
		i++;
	}
	ft_printf("r%d\n", read_arg(process, game, (size_t)i));
}
