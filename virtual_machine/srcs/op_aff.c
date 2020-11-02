/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 06:51:30 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/06 11:35:59 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"
#include "vm_op.h"

void			op_aff(t_process *process, t_game *game)
{
	char		reg_value;

	if (!process || !game)
		return ;
	reg_value = (char)(get_value_arg(*process, *game, 0, TRUE) % 255);
	if (game->flags & AFF)
		ft_printf("Aff: %c\n", reg_value);
}
