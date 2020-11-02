/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:36:22 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/24 19:05:06 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		init_game_map(t_game *game)
{
	size_t		i;

	if (!game)
		return ;
	i = 0;
	while (i < MEM_SIZE)
	{
		game->map[i] = 0;
		game->map_vs[i].value = 0;
		game->map_vs[i].id = 0;
		i++;
	}
}

/*
**   DESCRIPTION
** Function initializes an empty game with empty map and empty players
*/

t_game			init_game(void)
{
	t_game		game;
	size_t		i;

	game.cycle = 0;
	game.cycle_to_die = CYCLE_TO_DIE;
	game.cycle_to_check = game.cycle_to_die;
	game.nbr_live_op = 0;
	game.nbr_check = 0;
	game.flags = 0;
	game.dump_nbr = 0;
	game.dump_len = 32;
	game.last_live_player = 0;
	init_game_map(&game);
	i = 0;
	while (i <= MAX_PLAYERS)
	{
		init_player(&game.players[i], 0, "\0", "\0");
		game.players[i++].alive = 0;
	}
	return (game);
}
