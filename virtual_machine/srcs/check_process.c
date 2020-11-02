/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 07:04:41 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/25 11:02:33 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		print_death(t_process process, t_game game)
{
	t_uint32	nbr_cycles_without_life;

	nbr_cycles_without_life = game.cycle - process.live_last_cycle;
	ft_printf("Process %u hasn't lived for %u cycles (CTD %d)\n", process.id,
			nbr_cycles_without_life, game.cycle_to_die);
}

/*
**   DESCRIPTION
** The function checks processes and kills those who failed.
**
**   COMMENT
** If {game->cycle_to_die < 0} then every process will be killed.
*/

static void		check_alive_process(t_process **process, t_game *game)
{
	t_process	*tmp;
	t_process	*prev;

	if (!process || !*process || !game)
		return ;
	tmp = get_last_process(*process);
	while (tmp != NULL)
	{
		prev = tmp->prev;
		if (tmp->live_last_cycle <= game->cycle - game->cycle_to_die)
		{
			if (game->flags & DEBUG && game->debug_nbr & DEBUG_DEATH)
				print_death(*tmp, *game);
			if (tmp == *process)
				remove_one_process(process);
			else
				remove_one_process(&tmp);
		}
		tmp = prev;
	}
}

/*
**   DESCRIPTION
** The function checks processes and kills those who failed. The same function
** updates the CYCLE_TO_DIE value.
*/

void			check_game(t_process **process, t_game *game)
{
	if (!process || !*process || !game)
		return ;
	game->cycle_to_check--;
	if (game->cycle_to_check > 0)
		return ;
	game->nbr_check++;
	check_alive_process(process, game);
	if (game->nbr_check >= MAX_CHECKS || game->nbr_live_op >= NBR_LIVE)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->nbr_check = 0;
		if (game->flags & DEBUG && game->debug_nbr & DEBUG_CYCLES)
			ft_printf("Cycle to die is now %d\n", game->cycle_to_die);
	}
	game->nbr_live_op = 0;
	game->cycle_to_check = game->cycle_to_die;
}
