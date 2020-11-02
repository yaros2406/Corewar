/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:23:04 by frenna            #+#    #+#             */
/*   Updated: 2020/06/28 12:48:05 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "../libft/includes/libft.h"
# include "op.h"
# include "vm.h"
# include "vm_op.h"
# include "op.h"
# include <ncurses.h>
# include <time.h>

# define HEIGHT			(MEM_SIZE / 64 + 4)
# define WIDTH			(64 * 3 + 5)

# define ESC			27
# define SPACE			32

# define COLOR_GRAY		13

# define PLAYER_1		1
# define PLAYER_2		2
# define PLAYER_3		3
# define PLAYER_4		4
# define EMPTY			5
# define PLAYER_1_POS	6
# define PLAYER_2_POS	7
# define PLAYER_3_POS	8
# define PLAYER_4_POS	9
# define BORDER			10

/*
********************************************************************************
** >>> vs <<<
**
** structure for the visualisation purposes
**
** is_running
** - shows game status (running or paused)
**
** win_map
** - game map visualisation window
**
** win_info
** - window with information about the game progress
**
** status
** - game status to print
**
********************************************************************************
*/

typedef struct		s_vs
{
	t_bool			is_running;
	WINDOW			*win_map;
	WINDOW			*win_info;
	t_uint32		player_live_cycle[MAX_PLAYERS + 1];
	char			*status;
}					t_vs;

void				run_visual(t_game *game, t_process *process);
void				configure_vs(t_vs *vs);
void				vs_print(t_game *game, t_vs *vs, t_process *process);
int					get_color(int id);
void				print_vs_info(t_game *game, t_vs *vs, t_process *process);

#endif
