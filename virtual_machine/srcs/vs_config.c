/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:56:37 by frenna            #+#    #+#             */
/*   Updated: 2020/06/16 16:25:10 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"
#include <ncurses.h>

/*
**   DESCRIPTION
** Function to set configuration of the visual part
*/

void		configure_vs(t_vs *vs)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
	start_color();
	init_color(COLOR_GRAY, 355, 355, 355);
	init_pair(PLAYER_1, COLOR_GREEN, -1);
	init_pair(PLAYER_1_POS, -1, COLOR_GREEN);
	init_pair(PLAYER_2, COLOR_BLUE, -1);
	init_pair(PLAYER_2_POS, -1, COLOR_BLUE);
	init_pair(PLAYER_3, COLOR_RED, -1);
	init_pair(PLAYER_3_POS, -1, COLOR_RED);
	init_pair(PLAYER_4, COLOR_CYAN, -1);
	init_pair(PLAYER_4_POS, -1, COLOR_CYAN);
	init_pair(EMPTY, COLOR_GRAY, -1);
	init_pair(BORDER, COLOR_BLACK, 8);
	vs->win_map = newwin(HEIGHT, WIDTH + 4, 1, 40);
	vs->win_info = newwin(HEIGHT, 40, 1, 1);
}
