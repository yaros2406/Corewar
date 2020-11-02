/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 06:21:50 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/06 11:48:23 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_tab.h"
#include "vm_op.h"
#include "vm.h"
#include "op.h"

/*
**   DESCRIPTION
** The function checks the register index.
*/

static t_uint8		check_reg(const t_process process, t_game game,
					size_t index_arg)
{
	t_uint32		reg_position;
	t_uint32		reg_index;

	reg_position = get_position_arg(process, game, index_arg);
	reg_index = game.map[reg_position];
	return ((reg_index > 0) && (reg_index <= REG_NUMBER));
}

/*
**   DESCRIPTION
** The function checks the operation arguments.
**
**   COMMENT
** The function checks the encoding byte types and register index.
** If the operation does not have an encoding byte, then the operation has one
** argument of the TYPE_DIRECT type and verification is unnecessary.
*/

t_uint8				check_arg(t_process proc, t_game game)
{
	size_t			i;
	t_uint8			arg_code;
	t_op			op;

	op = g_op_tab[proc.op_code];
	if (op.arg_encoding == FALSE)
		return (TRUE);
	i = 0;
	while (i < (size_t)op.arg_num)
	{
		arg_code = get_type_arg(proc, game, i);
		if ((op.arg_type[i] & arg_code) == FALSE)
			return (FALSE);
		if (arg_code == REG_CODE && check_reg(proc, game, i) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
