/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 17:34:46 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/24 10:58:33 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**   DESCRIPTION
** The function displays all players
*/

void			print_hello(t_process *process, t_game *game)
{
	size_t		i_player;
	t_player	player;

	if (!process || !game)
		return ;
	i_player = 1;
	write(1, "Introducing contestants...\n", 27);
	while (process != NULL && i_player <= MAX_PLAYERS)
	{
		player = game->players[i_player];
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		i_player, player.code_size, player.name, player.comment);
		i_player++;
		process = process->next;
	}
}

/*
**   DESCRIPTION
** The function displays the name of the player who was last told that
** he was alive
**
**   COMMENT
** A format suitable for passing tests:
** "Contestant %d, \"%s\", has won !\n"
*/

void			print_winner(t_game *game)
{
	if (!game)
		return ;
	ft_printf("Player %d (%s) won\n", game->last_live_player,
	game->players[game->last_live_player].name);
}

/*
**   DESCRIPTION
** The function outputs memory in hex to standard output
** of dump_len octets per line
*/

void			print_map(t_game *game)
{
	size_t		i;

	if (!game)
		return ;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % game->dump_len))
			ft_printf("%s0x%04x : ", i ? "\n" : "", i);
		ft_printf("%02x ", game->map[i]);
		i++;
	}
	ft_printf("\n");
}
