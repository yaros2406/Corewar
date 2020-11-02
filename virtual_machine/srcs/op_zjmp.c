/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 06:58:25 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/25 17:50:45 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void			op_zjmp(t_process *process, t_game *game)
{
	t_int32		value;

	if (!process || !game)
		return ;
	value = get_value_arg(*process, *game, 0, TRUE) % IDX_MOD;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
	{
		print_op(*process);
		ft_printf("%d %s\n", get_value_arg(*process, *game, 0, TRUE),
			process->carry ? "OK" : "FAILED");
	}
	if (process->carry != FALSE)
	{
		process->pos = (t_uint32)crop_index((t_int32)process->pos + value);
		process->next_pos = process->pos;
	}
}
