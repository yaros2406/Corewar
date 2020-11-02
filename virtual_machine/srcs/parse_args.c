/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:30:58 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/21 15:01:36 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

/*
**   DESCRIPTION
** Function corrects id of all players and returns number of players
**
**   COMMENT
** If there are several players with the same id, then only the last player
** will have this id, the rest will be reset.
**
** If the player id > max number of players or id < 1, its id will be reset
*/

static size_t	get_player_nbr(t_player players[])
{
	int			i;
	int			j;
	size_t		player_nbr;

	player_nbr = 0;
	i = MAX_PLAYERS;
	while (i > 0)
	{
		if (players[i].alive)
		{
			player_nbr++;
			if (players[i].id > MAX_PLAYERS)
				players[i].id = 0;
			j = i - 1;
			while (j != -1 && players[i].id)
			{
				if (players[j].alive && players[j].id == players[i].id)
					players[j].id = 0;
				j--;
			}
		}
		i--;
	}
	return (player_nbr);
}

/*
**   DESCRIPTION
** The function returns the index of the player of the array players, whose id
** which best suits the required_id
**
**   COMMENT
** If player id is equal to required_id, return his index
**
** Further, if the player with the required_id index is not found, it is
** necessary to find the index of first player and the default id
**
** Further, if a player with a default id is not found, you must return the
** index of player with a minimum id
*/

static size_t	get_index_player(t_player players[], size_t required_id)
{
	size_t		i;
	size_t		i_player_with_first_zero_id;
	size_t		i_player_with_min_id;

	i_player_with_first_zero_id = 0;
	i_player_with_min_id = 0;
	i = 1;
	while (i <= MAX_PLAYERS)
	{
		if (players[i].alive)
		{
			if (players[i].id == required_id)
				return (i);
			if (players[i].id == 0 && i_player_with_first_zero_id == 0)
				i_player_with_first_zero_id = i;
			if ((players[i].id != 0 && i_player_with_min_id == 0)
			|| (players[i].id != 0 && i_player_with_min_id != 0
			&& players[i].id < players[i_player_with_min_id].id))
				i_player_with_min_id = i;
		}
		i++;
	}
	if (i_player_with_first_zero_id)
		return (i_player_with_first_zero_id);
	return (i_player_with_min_id);
}

/*
**   DESCRIPTION
** The function copies players from the players structure to the game structure
** from the accounts id of players
*/

static void		add_players_to_game(t_player players[], t_game *game)
{
	size_t		player_nbr;
	size_t		index_player;
	size_t		id;

	if (!(player_nbr = get_player_nbr(players)))
		put_error(USAGE, NULL);
	id = 1;
	while (id <= player_nbr)
	{
		if (!(index_player = get_index_player(players, id)))
			return ;
		copy_player(&players[index_player], &game->players[id]);
		players[index_player].alive = 0;
		id++;
	}
}

/*
**   DESCRIPTION
** The function parses the arguments of the program and writes the players and
** flags to the game structure
**
**   COMMENT
** First, the players are parsed into the players struct. After that,
** the add_players_to_game() function writes players to the game structure,
** but already in accordance with the players id
*/

void			parse_args(int ac, char **av, t_game *game)
{
	t_player	players[MAX_PLAYERS + 1];
	size_t		i;

	i = 0;
	while (i <= MAX_PLAYERS)
		clear_player(&players[i++]);
	av++;
	ac--;
	while (ac > 0)
	{
		if (*av && **av == '-')
			parse_flags(&av, &ac, players, game);
		else
			parse_file(*av, players, 0);
		av++;
		ac--;
	}
	add_players_to_game(players, game);
}
