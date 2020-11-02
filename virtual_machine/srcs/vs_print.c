/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 13:48:02 by frenna            #+#    #+#             */
/*   Updated: 2020/06/16 16:27:40 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

/*
**   DESCRIPTION
** Establish colors for game players and positions
*/

int				get_color(int id)
{
	if (id == 1)
		return (COLOR_PAIR(PLAYER_1));
	else if (id == 2)
		return (COLOR_PAIR(PLAYER_2));
	else if (id == 3)
		return (COLOR_PAIR(PLAYER_3));
	else if (id == 4)
		return (COLOR_PAIR(PLAYER_4));
	else if (id == 6)
		return (COLOR_PAIR(PLAYER_1_POS));
	else if (id == 7)
		return (COLOR_PAIR(PLAYER_2_POS));
	else if (id == 8)
		return (COLOR_PAIR(PLAYER_3_POS));
	else if (id == 9)
		return (COLOR_PAIR(PLAYER_4_POS));
	return (COLOR_PAIR(EMPTY));
}

static int		get_vs_color(t_process *process, int id, int color_id)
{
	while (process)
	{
		if ((int)crop_index_u(process->pos) == id)
			color_id += 5;
		process = process->next;
	}
	return (get_color(color_id));
}

/*
**   DESCRIPTION
** Print game map utilize functions
*/

static void		print_vs_map(t_game *game, t_vs *vs, t_process *process)
{
	int			i;
	int			j;
	int			color;
	int			id;

	i = 0;
	while (i < 64)
	{
		j = 0;
		wmove(vs->win_map, i + 2, 4);
		while (j < 64)
		{
			id = (int)game->map_vs[i * 64 + j].id;
			color = get_vs_color(process, i * 64 + j, id);
			wattron(vs->win_map, color);
			wprintw(vs->win_map, "%.2x", game->map[i * 64 + j]);
			wattroff(vs->win_map, color);
			waddch(vs->win_map, ' ');
			j++;
		}
		wprintw(vs->win_map, "\n");
		i++;
	}
}

static void		print_border(WINDOW *win)
{
	wattron(win, COLOR_PAIR(BORDER));
	wborder(win, 42, 42, 42, 42, 42, 42, 42, 42);
	wattroff(win, COLOR_PAIR(BORDER));
}

void			vs_print(t_game *game, t_vs *vs, t_process *process)
{
	werase(vs->win_map);
	werase(vs->win_info);
	print_vs_map(game, vs, process);
	print_vs_info(game, vs, process);
	print_border(vs->win_map);
	print_border(vs->win_info);
	wrefresh(vs->win_info);
	wrefresh(vs->win_map);
}
