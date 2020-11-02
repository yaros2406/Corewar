/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:05:50 by frenna            #+#    #+#             */
/*   Updated: 2020/06/29 17:51:43 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

/*
**   DESCRIPTION
** Set of functions to print information about the game process
*/

static void	set_vs_live_last(t_process *process, t_vs *vs)
{
	while (process)
	{
		if (process->live_last_id < MAX_PLAYERS + 1 && process->live_last_cycle
			> vs->player_live_cycle[process->live_last_id])
			vs->player_live_cycle[process->live_last_id] =
				process->live_last_cycle;
		process = process->next;
	}
}

static void	print_players(t_game *game, t_vs *vs, t_process *process)
{
	int	i;
	int	color;

	i = 1;
	set_vs_live_last(process, vs);
	while (i <= MAX_PLAYERS && game->players[i].alive == TRUE)
	{
		color = get_color(i);
		mvwprintw(vs->win_info, i * 4 + 2, 1, " Player %d : ", i);
		wattron(vs->win_info, color);
		wprintw(vs->win_info, "%.38s", game->players[i].name);
		wattroff(vs->win_info, color);
		mvwprintw(vs->win_info, i * 4 + 3, 2,
			"%-30s %zd", "   Last live:", vs->player_live_cycle[i]);
		mvwprintw(vs->win_info, i * 4 + 4, 2,
			"%-30s %zd", "   Cycles to wait:", process->cycle_to_exe);
		i++;
	}
}

static void	print_vs_winner(t_game *game, t_vs *vs)
{
	mvwprintw(vs->win_info, 40, 1, "Contestant %d, ", game->last_live_player);
	wattron(vs->win_info, get_color(game->last_live_player));
	wprintw(vs->win_info, "%.36s", game->players[game->last_live_player].name);
	wattroff(vs->win_info, get_color(game->last_live_player));
	mvwprintw(vs->win_info, 42, 1, ", has won !\n");
}

void		print_vs_info(t_game *game, t_vs *vs, t_process *process)
{
	wattron(vs->win_info, A_BOLD);
	mvwprintw(vs->win_info, 2, 1, "%25s", vs->status);
	mvwprintw(vs->win_info, 4, 1, " Cycle: %zd", game->cycle);
	print_players(game, vs, process);
	mvwprintw(vs->win_info, 24, 1, "%-30s %zd",
		" Number of live operations:", game->nbr_live_op);
	mvwprintw(vs->win_info, 26, 1, "%-30s %zd", " Number of checks:",
		game->nbr_check);
	mvwprintw(vs->win_info, 28, 1, "%-30s %d", " Cycles to die:",
		game->cycle_to_die);
	mvwprintw(vs->win_info, 30, 1, "%-30s %zd", " Cycles delta:",
		CYCLE_DELTA);
	if (!process->next)
		print_vs_winner(game, vs);
	wattroff(vs->win_info, A_BOLD);
}
