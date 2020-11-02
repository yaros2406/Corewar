/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:58 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_OP_H
# define VM_OP_H

# include "op.h"
# include "vm.h"
# include "../libft/includes/libft.h"

/*
********************************************************************************
** >>> Operation arguments <<<
********************************************************************************
*/

t_uint8					get_type_arg(t_process process, t_game game,
						size_t index_arg);

t_uint8					get_size_arg(t_process process, t_game game,
						size_t index_arg);

t_uint32				get_position_arg(t_process process, t_game game,
						size_t index_arg);

t_int32					read_arg(t_process process, t_game game,
						size_t index_arg);

t_int32					get_value_arg(t_process process, t_game game,
						size_t index_arg, t_uint8 idx_mode);

t_uint8					check_arg(t_process proc, t_game game);

/*
********************************************************************************
** >>> Work with bits <<<
********************************************************************************
*/

t_int32					read_byte(const t_uint8 *map, t_uint32 position,
						t_uint32 size);

void					write_byte(t_game *game, t_uint32 position,
						t_int32 value, t_uint32 id);

#endif
