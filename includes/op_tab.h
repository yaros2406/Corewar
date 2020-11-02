/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_tab.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 06:48:55 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 12:43:56 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_OP_TAB_H
# define VM_OP_TAB_H

# include "op.h"
# include "types.h"

/*
********************************************************************************
** >>> Operation <<<
**
**   DESCRIPTION
** The "Operation" structure contains basic data on assembly language operations
**
**   .name
** Name of operation
**
**   .arg_num
** Number of arguments
**
**   .arg_type
** Possible argument types
**
**   .code
** COde of operation
**
**   .cycles
** The number of cycles to wait before executing
**
**   .arg_encoding
** A flag that indicates whether argument types are encoded. 1 - encoded byte,
** 0 - no. If encoded byte it's ABCDEFGH bits, than:
** AB - first argument code
** CD - second argument code
** EF - third argument code
** GH - fourth argument code
**
**   .carry
** A flag that indicates whether the operation affects the "carry" property of
** the operation. See also >>> Operation <<<
**
**   .dir_size
** T_DIR type argument size
********************************************************************************
*/

typedef struct			s_op
{
	char				*name;
	t_uint8				arg_num;
	t_uint8				arg_type[MAX_ARGS_NUMBER];
	t_uint8				code;
	t_uint32			cycles;
	t_uint8				arg_encoding;
	t_uint8				carry;
	t_uint8				dir_size;
}						t_op;

static t_op				g_op_tab[17] =
{
	{
		.name = 0,
		.arg_num = 0,
		.arg_type = {0},
		.code = 0,
		.cycles = 0,
		.arg_encoding = 0,
		.carry = 0,
		.dir_size = 0
	},
	{
		.name = "live",
		.arg_num = 1,
		.arg_type = {T_DIR},
		.code = 1,
		.cycles = 10,
		.arg_encoding = FALSE,
		.carry = FALSE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "ld",
		.arg_num = 2,
		.arg_type = {T_DIR | T_IND, T_REG},
		.code = 2,
		.cycles = 5,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "st",
		.arg_num = 2,
		.arg_type = {T_REG, T_IND | T_REG},
		.code = 3,
		.cycles = 5,
		.arg_encoding = TRUE,
		.carry = FALSE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "add",
		.arg_num = 3,
		.arg_type = {T_REG, T_REG, T_REG},
		.code = 4,
		.cycles = 10,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "sub",
		.arg_num = 3,
		.arg_type = {T_REG, T_REG, T_REG},
		.code = 5,
		.cycles = 10,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "and",
		.arg_num = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.code = 6,
		.cycles = 6,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "or",
		.arg_num = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.code = 7,
		.cycles = 6,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "xor",
		.arg_num = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.code = 8,
		.cycles = 6,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "zjmp",
		.arg_num = 1,
		.arg_type = {T_DIR},
		.code = 9,
		.cycles = 20,
		.arg_encoding = FALSE,
		.carry = FALSE,
		.dir_size = DIR_SHORT,
	},
	{
		.name = "ldi",
		.arg_num = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.code = 10,
		.cycles = 25,
		.arg_encoding = TRUE,
		.carry = FALSE,
		.dir_size = DIR_SHORT,
	},
	{
		.name = "sti",
		.arg_num = 3,
		.arg_type = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.code = 11,
		.cycles = 25,
		.arg_encoding = TRUE,
		.carry = FALSE,
		.dir_size = DIR_SHORT,
	},
	{
		.name = "fork",
		.arg_num = 1,
		.arg_type = {T_DIR},
		.code = 12,
		.cycles = 800,
		.arg_encoding = FALSE,
		.carry = FALSE,
		.dir_size = DIR_SHORT,
	},
	{
		.name = "lld",
		.arg_num = 2,
		.arg_type = {T_DIR | T_IND, T_REG},
		.code = 13,
		.cycles = 10,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SIZE,
	},
	{
		.name = "lldi",
		.arg_num = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.code = 14,
		.cycles = 50,
		.arg_encoding = TRUE,
		.carry = TRUE,
		.dir_size = DIR_SHORT,
	},
	{
		.name = "lfork",
		.arg_num = 1,
		.arg_type = {T_DIR},
		.code = 15,
		.cycles = 1000,
		.arg_encoding = FALSE,
		.carry = FALSE,
		.dir_size = DIR_SHORT,
	},
	{
		.name = "aff",
		.arg_num = 1,
		.arg_type = {T_REG},
		.code = 16,
		.cycles = 2,
		.arg_encoding = TRUE,
		.carry = FALSE,
		.dir_size = DIR_SIZE,
	},
};

#endif
