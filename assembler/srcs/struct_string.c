/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 07:40:59 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 13:56:52 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**   DESCRIPTION
** The function copy string data
*/

static void		copy_data(char *to, const char *from, size_t size)
{
	size_t		i;

	if (!to || !from)
		return ;
	i = 0;
	while (i < size)
	{
		to[i] = from[i];
		i++;
	}
	to[i] = 0;
}

/*
**   DESCRIPTION
** The function resize string data size
*/

int				resize_string(t_string **string, size_t new_mem_size)
{
	char		*new_data;

	if (!string || new_mem_size <= 0)
		return (0);
	if (!(new_data = (char *)malloc(sizeof(char) * (new_mem_size + 1))))
	{
		remove_string(string);
		return (0);
	}
	copy_data(new_data, (*string)->data, (*string)->size);
	if ((*string)->data)
		free((*string)->data);
	(*string)->data = new_data;
	(*string)->mem = new_mem_size;
	return (1);
}

/*
**   DESCRIPTION
** The function free string
*/

void			remove_string(t_string **string)
{
	if (!string || !*string)
		return ;
	if ((*string)->data)
		free((*string)->data);
	(*string)->data = NULL;
	free(*string);
	*string = NULL;
}

/*
**   DESCRIPTION
** The function moves the string pointer forward by a string of LEN characters
**
**   COMMENT
** The function also counts the current line in the file and the row
*/

void			move_str_pointer(t_string *string, size_t len)
{
	if (!string->data[string->i] || len <= 0)
		return ;
	if (string->data[string->i] == '\n')
	{
		string->line++;
		string->row = 1;
	}
	else
		string->row++;
	string->i++;
	move_str_pointer(string, len - 1);
}

/*
**   DESCRIPTION
** The function creates a string with a dynamic array
*/

t_string		*init_string(size_t mem)
{
	t_string	*new_string;
	size_t		i;

	if (!(new_string = (t_string *)malloc(sizeof(t_string))))
		return (NULL);
	if (!(new_string->data = (char *)malloc(sizeof(char) * (mem + 1))))
	{
		free(new_string);
		return (NULL);
	}
	new_string->size = 0;
	new_string->mem = mem;
	new_string->i = 0;
	new_string->line = 1;
	new_string->row = 1;
	i = 0;
	while (i <= mem)
		new_string->data[i++] = '\0';
	return (new_string);
}
