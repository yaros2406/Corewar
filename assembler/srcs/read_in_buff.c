/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:38:46 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 10:06:06 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**   DESCRIPTION
** The function reads a file to a dynamic array and returns it
*/

t_string		*read_file(int fd)
{
	ssize_t		read_byte;
	t_string	*buff;

	if (!(buff = init_string(BUFF_READ)))
		return (NULL);
	while (1)
	{
		if (buff->size + BUFF_READ > buff->mem)
			if (!(resize_string(&buff, buff->mem * 2)))
			{
				remove_string(&buff);
				return (NULL);
			}
		read_byte = read(fd, buff->data + buff->size, BUFF_READ);
		buff->size += (size_t)read_byte;
		buff->data[buff->size] = '\0';
		if (read_byte <= 0)
			return (buff);
	}
}
