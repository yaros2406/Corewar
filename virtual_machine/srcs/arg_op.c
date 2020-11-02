/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 09:49:14 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 06:08:28 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_tab.h"
#include "vm_op.h"

/*
**   DESCRIPTION
** The function returns the type of the argument, which is encoded under the
** index "index_arg" in the byte encoding
**
**   RETURN VALUE
** Type of argument
**
**   COMMENT
** If index_arg != [0..<MAX_ARG_NUMBERS], the behavior is undefined.
*/

t_uint8			get_type_arg(t_process process, t_game game, size_t index_arg)
{
	t_uint8		byte_encoding_args;
	t_uint8		arg_code;

	if (g_op_tab[process.op_code].arg_encoding == FALSE)
		return (T_DIR);
	byte_encoding_args = game.map[crop_index_u(process.pos + OP_CODE_LEN)];
	arg_code = (byte_encoding_args >> ((3 - index_arg) * 2)) & 0b00000011;
	if (arg_code == REG_CODE)
		return (T_REG);
	else if (arg_code == DIR_CODE)
		return (T_DIR);
	else if (arg_code == IND_CODE)
		return (T_IND);
	else
		return (FALSE);
}

/*
**   DESCRIPTION
** The function returns the size of the argument, which is encoded under the
** index "index_arg" in the byte encoding
**
**   RETURN VALUE
** Size of argument
**
**   COMMENT
** If index_arg != [0..<MAX_ARGS_NUMBER] or type of operation invalid, the
** behavior is undefined.
*/

t_uint8			get_size_arg(t_process process, t_game game, size_t index_arg)
{
	t_uint8		arg_type;
	t_op		op;

	op = g_op_tab[process.op_code];
	arg_type = get_type_arg(process, game, index_arg);
	if (arg_type == T_REG)
		return (1);
	else if (arg_type == T_IND)
		return (IND_SIZE);
	else if (arg_type == T_DIR)
		return (op.dir_size);
	else
		return (FALSE);
}

/*
**   DESCRIPTION
** The function returns the index of the array (game.map) from which the
** argument of the operation begins with the index_arg
**
**   RETURN VALUE
** Position of the beginning of the i-th argument of the operation
**
**   COMMENT
** If index_arg != [0..<MAX_ARGS_NUMBER] or type of operation invalid, the
** behavior is undefined.
*/

t_uint32		get_position_arg(t_process process, t_game game,
				size_t index_arg)
{
	size_t		i;
	t_uint32	position;
	t_op		op;

	op = g_op_tab[process.op_code];
	position = process.pos + OP_CODE_LEN;
	if (op.arg_encoding == FALSE)
		return (crop_index_u(position));
	position += ARG_CODE_LEN;
	i = 0;
	while (i < index_arg && i <= MAX_ARGS_NUMBER)
	{
		position += get_size_arg(process, game, i);
		i++;
	}
	return (crop_index_u(position));
}

/*
**   DESCRIPTION
** The function returns the #(index_arg) argument of the operation
**
**   RETURN VALUE
** Argument of the operation
**
**   COMMENT
** The function returns the #(index_arg) argument of the operation, not the
** value of this argument.
**
** Cases:
** TYPE_REGISTRY	will return the register number		("r10" -> "10")
** TYPE_DIRECT		will return the value				("%20" -> "20")
** TYPE_INDIRECT	will return the address				("-30" -> "-30")
*/

t_int32			read_arg(t_process process, t_game game, size_t index_arg)
{
	t_uint8		arg_type;
	t_uint32	arg_position;
	t_op		op;

	op = g_op_tab[process.op_code];
	if (op.arg_encoding == FALSE)
		return (read_byte(game.map, process.pos + OP_CODE_LEN, op.dir_size));
	arg_type = get_type_arg(process, game, index_arg);
	arg_position = get_position_arg(process, game, index_arg);
	if (arg_type == T_REG)
		return (read_byte(game.map, arg_position, 1));
	else if (arg_type == T_IND)
		return (read_byte(game.map, arg_position, IND_SIZE));
	else if (arg_type == T_DIR)
		return (read_byte(game.map, arg_position, op.dir_size));
	else
		return (0);
}

/*
**   DESCRIPTION
** The function returns the value of #(index_arg) argument of the operation
**
**   RETURN VALUE
** Value of argument of the operation
**
**   COMMENT
** The function returns the value of #(index_arg) argument of the operation
**
** Cases:
** TYPE_REGISTRY	will return the value of the register. The register index
** 					is read from the map using the read_arg() function
** 					("r10" -> return value reg[10] -> 3456)
** TYPE_DIRECT		will return the value
** 					("%20" -> "20")
** TYPE_INDIRECT	will return 4 bytes read from the map. The address
**					for reading is taken from the map function read_arg()
**					("-5" -> read 4 byte from address (pos + (-5)).
**					If idx_mode == TRUE then crop address on IDX_MOD. Read 4
**					byte from address and return read value)
*/

t_int32			get_value_arg(t_process process, t_game game, size_t index_arg,
				t_uint8 idx_mode)
{
	t_op		op;
	t_uint8		arg_type;
	t_int32		arg;
	t_uint32	ind_pos;

	op = g_op_tab[process.op_code];
	if (!op.arg_encoding)
		return (read_byte(game.map, process.pos + OP_CODE_LEN, op.dir_size));
	arg_type = get_type_arg(process, game, index_arg);
	arg = read_arg(process, game, index_arg);
	if (arg_type == T_REG)
		return (process.reg[arg]);
	else if (arg_type == T_DIR)
		return (arg);
	else if (arg_type == T_IND)
	{
		arg = (idx_mode == TRUE) ? arg % IDX_MOD : arg;
		ind_pos = process.pos + arg;
		return (read_byte(game.map, ind_pos,
				op.code == 13 ? IND_SIZE : DIR_SIZE));
	}
	return (FALSE);
}
