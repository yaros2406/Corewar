/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 07:14:24 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/25 19:23:35 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

static void			set_position(t_process *process, t_int32 nbr_players)
{
	t_int32			i;

	if (process == NULL || (nbr_players == 0 || nbr_players > MAX_PLAYERS))
		return ;
	process = get_first_process(process);
	i = 0;
	while (process != NULL)
	{
		process->pos = (t_uint32)(MEM_SIZE / nbr_players * i);
		i++;
		process = process->next;
	}
}

static t_process	*set_processes(t_game *game)
{
	t_process		*process;
	t_int32			nbr_player;
	size_t			i;

	if (!game)
		return (NULL);
	process = NULL;
	nbr_player = 0;
	i = 0;
	while (i <= MAX_PLAYERS)
	{
		if (game->players[i].alive == TRUE)
		{
			nbr_player++;
			if ((add_process(&process, nbr_player * -1) == FALSE))
			{
				remove_process(&process);
				return (NULL);
			}
		}
		i++;
	}
	set_position(process, nbr_player);
	return (process);
}

static void			set_map(t_process *process, t_game *game)
{
	t_process		*current_process;
	size_t			player;
	size_t			i;

	if (!game)
		return ;
	current_process = process;
	player = 1;
	while (current_process)
	{
		i = 0;
		while (i < (size_t)game->players[player].code_size)
		{
			game->map[crop_index(current_process->pos + i)] =
				game->players[player].executable_code[i];
			i++;
		}
		game->last_live_player = (t_uint32)player;
		current_process = current_process->next;
		player++;
	}
}

static int			is_dump_cycles(t_game *game)
{
	if ((game->flags & DUMP) && (game->cycle == game->dump_nbr))
	{
		print_map(game);
		return (1);
	}
	game->cycle += 1;
	if (game->flags & DEBUG && game->debug_nbr & DEBUG_CYCLES)
		ft_printf("It is now cycle %u\n", game->cycle);
	return (0);
}

void				run_game(t_game *game)
{
	t_process		*process;

	if (!game)
		return ;
	if ((process = set_processes(game)) == NULL)
		return ;
	set_map(process, game);
	if (game->flags & VISUAL)
		run_visual(game, process);
	else
	{
		print_hello(process, game);
		while (process != NULL)
		{
			if (is_dump_cycles(game))
				return (remove_process(&process));
			execute_process(process, game);
			check_game(&process, game);
		}
		remove_process(&process);
		print_winner(game);
	}
}
