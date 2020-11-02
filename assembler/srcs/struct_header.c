/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 15:08:03 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 09:54:07 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

/*
**   DESCRIPTION
** The function clears the array
*/

static void		clear_arr(char arr[], size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
		arr[i++] = 0;
}

/*
**   DESCRIPTION
** The function returns T_HEADER with null values
*/

t_header		init_header(void)
{
	t_header	new;

	new.magic = COREWAR_EXEC_MAGIC;
	new.prog_size = 0;
	clear_arr(new.prog_name, PROG_NAME_LENGTH + 1);
	clear_arr(new.comment, COMMENT_LENGTH + 1);
	return (new);
}
