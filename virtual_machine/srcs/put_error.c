/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:37:28 by frenna            #+#    #+#             */
/*   Updated: 2020/06/06 14:24:51 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_error(int error, char *s)
{
	if (error == ERR_FLAG)
		ft_printf("Can't read source file %s\n", s);
	else if (error == ERR_FILE)
		ft_printf("Invalid file %s\n", s);
	else if (error == L_SIZE)
		ft_printf("File %s code size is too big\n", s);
	else if (error == M_SIZE)
		ft_printf("File %s code size is too small\n", s);
	else if (error == ERR_DS)
		ft_printf("File %s has a code size that differs from what its header "
		"says\n", s);
	else if (error == ERR_MANY)
		ft_printf("Too many players\n");
	else if (error == ERR_MALLOC)
		ft_printf("Memory not allocated\n");
	else if (error == USAGE)
		ft_printf("Usage: ./corewar [-aff] [-dump nbr_cycles] [[-n number] "
		"champion1.cor] ...\n");
	exit(EXIT_FAILURE);
}
