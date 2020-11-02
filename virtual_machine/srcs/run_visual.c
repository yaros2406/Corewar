/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_visual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:45:00 by frenna            #+#    #+#             */
/*   Updated: 2020/06/30 08:01:06 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

/*
**   DESCRIPTION
** Function to fill map_vs with player ids
*/

static void	init_vs_process(t_process *process, t_game *game)
{
	t_int32	i;

	while (process)
	{
		i = 0;
		while (i < game->players[process->player_id].code_size)
		{
			game->map_vs[crop_index(process->pos + i)].id = process->player_id;
			i++;
		}
		process = process->next;
	}
}

/*
**   DESCRIPTION
** Change game status on press space button
*/

static void	vs_change_status(t_vs *vs)
{
	if (vs->is_running == FALSE)
	{
		vs->is_running = TRUE;
		vs->status = "** RUNNING **";
	}
	else
	{
		vs->is_running = FALSE;
		vs->status = "** PAUSED **";
	}
}

/*
**   DESCRIPTION
** Execute game process
*/

static void	execute_vs_process(t_process *process, t_game *game, t_vs *vs)
{
	t_process	*tmp;

	tmp = process;
	while (getch() != ESC)
	{
		while (process != NULL)
		{
			if (getch() == ESC)
				break ;
			vs_print(game, vs, tmp);
			if (getch() == SPACE)
				vs_change_status(vs);
			if (vs->is_running == TRUE)
			{
				game->cycle++;
				execute_process(process, game);
				check_game(&process, game);
				vs_print(game, vs, tmp);
			}
		}
	}
	endwin();
	remove_process(&process);
}

void		run_visual(t_game *game, t_process *process)
{
	t_vs	vs;
	int		i;

	if (game->flags & DEBUG)
		game->flags &= ~DEBUG;
	i = 0;
	while (i < MAX_PLAYERS + 1)
		vs.player_live_cycle[i++] = 0;
	vs.is_running = FALSE;
	vs.win_map = NULL;
	vs.win_info = NULL;
	vs.status = "** PAUSED **";
	configure_vs(&vs);
	init_vs_process(process, game);
	execute_vs_process(process, game, &vs);
}
