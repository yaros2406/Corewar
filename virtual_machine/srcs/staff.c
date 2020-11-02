/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:00:56 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/05 11:25:41 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**   DESCRIPTION
** Operation crop_index() and crop_index_u() truncates the value included in the
** range [0..<MEM_SIZE]. The resulting value is used as an index in the
** game.memory array, which prevents going beyond it.
** See also >>> Game <<<
**
**   INPUT VALUE
** crop_index() works with signed values t_int32, crop_index_u works with
** unsigned values t_uint32
**
**   RETURN VALUE
** The crop value.
*/

t_uint32		crop_index(t_int32 address)
{
	return (t_uint32)((MEM_SIZE + address % MEM_SIZE) % MEM_SIZE);
}

t_uint32		crop_index_u(t_uint32 address)
{
	return (crop_index((t_int32)address));
}

/*
**   DESCRIPTION
** The function reads bytes from the map, converts it to a number and returns it
**
**   COMMENT
** If size > 4 or size <= 0, undefined behavior
*/

t_int32			read_byte(const t_uint8 *map, t_uint32 position,
				t_uint32 size)
{
	t_uint32	i;
	t_uint32	result;

	if (!map || !size)
		return (0);
	i = 0;
	result = 0;
	while (i < size)
	{
		result = (result << 8) + map[crop_index_u(position + i)];
		i++;
	}
	if (result >> (size * 8 - 1))
		result |= (0xffffffff << (size * 8 - 1) << 1);
	return ((t_int32)result);
}
