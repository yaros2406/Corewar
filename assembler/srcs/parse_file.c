/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 07:32:32 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 10:03:03 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

/*
**   DESCRIPTION
** The function returns fd. If the file cannot be read, it returns 0
*/

static int		open_file(char *file_name)
{
	int			fd;
	char		c;

	if (!file_name)
		return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || (read(fd, &c, 0)) < 0)
	{
		put_error(FILE_ERR, file_name);
		return (0);
	}
	return (fd);
}

/*
**   DESCRIPTION
** The function turns the read file into a list of tokens and returns it
**
**   COMMENT
** The function reads the file to a dynamic buffer array. Then a list of file
** tokens is created from the buffer. If the file is not valid or there is a
** lexical error, the function outputs the error to standard output, free the
** token memory, and returns NULL
*/

t_token			*parse_file(char *file_name)
{
	t_token		*tokens;
	t_string	*buff;
	int			fd;

	if (!file_name || !(fd = open_file(file_name)))
		return (NULL);
	if (!(buff = read_file(fd)))
	{
		put_error(ALLOC_ERR, NULL);
		return (NULL);
	}
	buff->file_name = file_name;
	tokens = parse_from_buff(buff);
	remove_string(&buff);
	return (tokens);
}
