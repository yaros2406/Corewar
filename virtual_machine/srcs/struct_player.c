/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 09:44:30 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/05 11:29:24 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		clear_array(char *array, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
		array[i++] = 0;
}

/*
**   DESCRIPTION
** The function sets defaults for the player.
*/

void			clear_player(t_player *player)
{
	player->id = FALSE;
	player->alive = FALSE;
	player->code_size = FALSE;
	clear_array(player->name, PROG_NAME_LENGTH + 1);
	clear_array(player->comment, COMMENT_LENGTH + 1);
	clear_array((char *)player->executable_code, CHAMP_MAX_SIZE + 1);
}

/*
**   DESCRIPTION
** Function initializes an player
*/

void			init_player(t_player *new, size_t id, char *name, char *comment)
{
	clear_player(new);
	new->id = id;
	new->alive = TRUE;
	new->code_size = 0;
	ft_strcpy(new->name, name);
	ft_strcpy(new->comment, comment);
}

/*
**   DESCRIPTION
** Function copy from -> to
*/

void			copy_player(t_player *from, t_player *to)
{
	size_t		i;

	if (!from || !to)
		return ;
	to->id = from->id;
	to->alive = from->alive;
	to->code_size = from->code_size;
	ft_strcpy(to->name, from->name);
	ft_strcpy(to->comment, from->comment);
	i = 0;
	while (i < CHAMP_MAX_SIZE)
	{
		to->executable_code[i] = from->executable_code[i];
		i++;
	}
}
