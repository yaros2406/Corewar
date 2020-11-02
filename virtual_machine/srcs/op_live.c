/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 10:12:25 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/30 09:26:28 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

static void		print_debug_op_live(t_process process, t_game game)
{
	if (game.flags & DEBUG && game.debug_nbr & DEBUG_OP)
	{
		print_op(process);
		ft_printf("%d\n", get_value_arg(process, game, 0, TRUE));
	}
}

static void		print_debug_alive(t_game game, t_int32 index_player)
{
	if (game.flags & DEBUG && game.debug_nbr & DEBUG_LIVES)
	{
		ft_printf("Player %d (%s) is said to be alive\n", index_player,
			game.players[index_player].name);
	}
}

static void		print_alive(t_game game, t_int32 index_player)
{
	if (!(game.flags & VISUAL))
		ft_printf("A process shows that player %d (%s) is alive\n",
			index_player, game.players[index_player].name);
}

static int		is_valid_live_op(t_game game, t_int32 index_player)
{
	if (index_player > 0 && index_player <= MAX_PLAYERS
	&& game.players[index_player].alive == TRUE)
		return (TRUE);
	return (FALSE);
}

void			op_live(t_process *process, t_game *game)
{
	t_int32		index_player;

	if (!process || !game)
		return ;
	index_player = -1 * get_value_arg(*process, *game, 0, TRUE);
	process->live_last_id = index_player;
	process->live_last_cycle = game->cycle;
	print_debug_op_live(*process, *game);
	if (is_valid_live_op(*game, index_player))
	{
		game->last_live_player = index_player;
		print_debug_alive(*game, index_player);
		print_alive(*game, index_player);
	}
	game->nbr_live_op += 1;
}
