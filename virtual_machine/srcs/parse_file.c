/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 17:56:18 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/21 15:02:23 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

/*
**   DESCRIPTION
** The function reads 4 bytes, converts them to a number and returns it.
*/

static t_int32		read_int(t_int32 fd)
{
	t_uint8			bite;
	t_uint32		result;
	t_int32			i;

	result = 0;
	i = 0;
	while (i < 4)
	{
		read(fd, &bite, 1);
		result = (result << 8) + bite;
		i++;
	}
	return ((t_int32)result);
}

/*
**   DESCRIPTION
** The function returns the file descriptor and checks that there is such a
** file, we have the necessary access, this is not a directory
** and the file has a valid magic_number
*/

static t_int32		get_fd(char *file_name)
{
	t_int32			fd;

	if ((fd = (t_int32)open(file_name, O_RDONLY)) < 0)
		put_error(ERR_FLAG, file_name);
	if (read_int(fd) != COREWAR_EXEC_MAGIC)
		put_error(ERR_FILE, file_name);
	return ((t_int32)fd);
}

/*
**   DESCRIPTION
** The function parses the file into the players array
**
**   COMMENT
** 1. Get the file descriptor and check magic number in function get_fd()
** 2. Read the max name size
** 3. Read zero bytes into the zero_byte variable
** 4. Read the size of the source code and check it
** 5. Read max comment size
** 6. Read zero bytes again and check old and just read zero bytes
** 7. Read the source code and check the their size
**
** Any failed checks and the program will terminate prematurely
*/

void				parse_file(char *file_name, t_player players[], size_t id)
{
	t_int32			fd;
	t_int32			cod_size;
	t_int32			zero_byte;
	static size_t	i_player = 0;

	if (!file_name)
		return ;
	if (++i_player > MAX_PLAYERS)
		put_error(ERR_MANY, file_name);
	fd = get_fd(file_name);
	players[i_player].id = id;
	players[i_player].alive = TRUE;
	read(fd, players[i_player].name, PROG_NAME_LENGTH);
	zero_byte = read_int(fd);
	cod_size = read_int(fd);
	if ((players[i_player].code_size = cod_size) > CHAMP_MAX_SIZE || !cod_size)
		put_error(cod_size ? L_SIZE : M_SIZE, file_name);
	read(fd, players[i_player].comment, COMMENT_LENGTH);
	if (zero_byte || read_int(fd))
		put_error(ERR_FILE, file_name);
	if (read(fd, players[i_player].executable_code, cod_size) < cod_size)
		put_error(ERR_FILE, file_name);
	if (read(fd, &zero_byte, 1))
		put_error(ERR_DS, file_name);
	close(fd);
}
