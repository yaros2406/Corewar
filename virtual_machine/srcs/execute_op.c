/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 07:06:02 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 09:10:14 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_tab.h"
#include "op_tab_func.h"
#include "vm_op.h"

/*
**   DESCRIPTION
** The function returns the current position + length of the current operation.
**
**   COMMENT
** If this is a zjmp() (operation code is 9) operation and there is a carry
** flag, then the operation has already updated its position.
*/

static t_uint32		get_next_position(t_process process, t_game game)
{
	t_op			op;
	t_uint32		new_position;
	size_t			i;

	op = g_op_tab[process.op_code];
	if (op.arg_encoding == FALSE)
		return (crop_index_u(process.pos + OP_CODE_LEN + op.dir_size));
	new_position = process.pos + OP_CODE_LEN + ARG_CODE_LEN;
	i = 0;
	while (i < (size_t)op.arg_num)
	{
		new_position += (t_uint32)get_size_arg(process, game, i);
		i++;
	}
	new_position = crop_index_u(new_position);
	return (new_position);
}

/*
**   DESCRIPTION
** Function performs the operation of the current process
**
**   COMMENT
** The first condition is to check the {cycle_to_exe} of process.
** if {cycle_to_exe} means in the previous cycle the process has moved.
** Get the code for the new operation. If it is valid, remember the operation
** code, otherwise we will go to the next byte.
**
** Next, reduce the number of cycles before execution. If this value is zero,
** check the arguments. And if successful, we perform the operation. Then,
** in any case, we move the process forward by the length of the operation
*/

static void			execute_current_process(t_process *process, t_game *game)
{
	if (!process || !game)
		return ;
	if (process->cycle_to_exe == 0)
	{
		if (game->map[process->pos] <= 0 || game->map[process->pos] > 16)
		{
			process->pos = crop_index_u(process->pos + 1);
			return ;
		}
		process->op_code = game->map[process->pos];
		process->cycle_to_exe = g_op_tab[process->op_code].cycles;
	}
	if (process->cycle_to_exe > 0)
		process->cycle_to_exe--;
	if (process->cycle_to_exe == 0)
	{
		process->next_pos = get_next_position(*process, *game);
		if (check_arg(*process, *game))
		{
			g_op_func[process->op_code](process, game);
		}
		print_next_position(*process, *game);
		process->pos = process->next_pos;
	}
}

/*
**   DESCRIPTION
** The function goes through all the processes and checks the possibility
** of the operation. If the check succeed, the operation is performed
** and the process moves to the next position.
*/

void				execute_process(t_process *process, t_game *game)
{
	if (!process || !game)
		return ;
	process = get_last_process(process);
	while (process != NULL)
	{
		execute_current_process(process, game);
		process = process->prev;
	}
}
