/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 06:53:25 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/25 17:55:32 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void			op_fork(t_process *process, t_game *game)
{
	t_int32		move_to;
	t_uint32	new_address;
	t_process	*last_process;

	if (!process || !game)
		return ;
	move_to = get_value_arg(*process, *game, 0, TRUE) % IDX_MOD;
	new_address = (t_uint32)crop_index(move_to + (t_int32)process->pos);
	last_process = get_last_process(process);
	last_process->next = copy_process(process, last_process, new_address);
	if (last_process->next == NULL)
	{
		remove_process(&process);
		put_error(ERR_MALLOC, NULL);
	}
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
	{
		print_op(*process);
		ft_printf("%d (%d)\n", get_value_arg(*process, *game, 0, TRUE),
			move_to + (t_int32)process->pos);
	}
}

void			op_lfork(t_process *process, t_game *game)
{
	t_int32		move_to;
	t_uint32	new_address;
	t_process	*last_process;

	if (!process || !game)
		return ;
	move_to = get_value_arg(*process, *game, 0, TRUE);
	new_address = (t_uint32)crop_index(move_to + (t_int32)process->pos);
	last_process = get_last_process(process);
	last_process->next = copy_process(process, last_process, new_address);
	if (last_process->next == NULL)
	{
		remove_process(&process);
		put_error(ERR_MALLOC, NULL);
	}
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_OP)
	{
		print_op(*process);
		ft_printf("%d (%d)\n", move_to, move_to + process->pos);
	}
}
