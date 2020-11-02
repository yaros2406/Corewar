/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:07:56 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 06:23:55 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_TAB_FUNC_H
# define OP_TAB_FUNC_H

# include "vm.h"
# include "op_tab.h"

void					op_live(t_process *process, t_game *game);

void					op_ld(t_process *process, t_game *game);

void					op_st(t_process *process, t_game *game);

void					op_add(t_process *process, t_game *game);

void					op_sub(t_process *process, t_game *game);

void					op_and(t_process *process, t_game *game);

void					op_or(t_process *process, t_game *game);

void					op_xor(t_process *process, t_game *game);

void					op_zjmp(t_process *process, t_game *game);

void					op_ldi(t_process *process, t_game *game);

void					op_sti(t_process *process, t_game *game);

void					op_fork(t_process *process, t_game *game);

void					op_lld(t_process *process, t_game *game);

void					op_lldi(t_process *process, t_game *game);

void					op_lfork(t_process *process, t_game *game);

void					op_aff(t_process *process, t_game *game);

typedef void			(*t_op_func)(t_process *process, t_game *game);

static t_op_func		g_op_func[17] =
{
	NULL,
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff
};

#endif
