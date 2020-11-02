/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:53:58 by frenna            #+#    #+#             */
/*   Updated: 2020/06/24 19:22:20 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int ac, char **av)
{
	t_game	game;

	if (ac > 1)
	{
		game = init_game();
		parse_args(ac, av, &game);
		run_game(&game);
	}
	else
		ft_printf("Usage: ./corewar [-aff] [-dump nbr_cycles] [[-n number] "
		"champion1.cor] ...\n");
	return (0);
}
