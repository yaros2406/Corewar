/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:17:11 by frenna            #+#    #+#             */
/*   Updated: 2020/06/23 16:42:24 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int				ft_atoi(const char *str)
{
	__int128_t	f;
	int			sign;

	if (!str)
		return (0);
	f = 0;
	sign = 1;
	if (*str == '+' || (*str == '-' && (sign = -1)))
		str++;
	while (is_digit(*str) && f < ATOI_MAX)
		f = (f << 3) + (f << 1) + *str++ + (~0x30 + 1);
	if (f >= ATOI_MAX)
		f = sign < 0 ? 0 : -1;
	return ((int)f * sign);
}
