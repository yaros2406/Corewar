/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:33:03 by frenna            #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

int		is_num(char *s)
{
	size_t	nbr_len;
	size_t	sign;

	if (!s)
		return (0);
	while (ft_isspace(*s))
		s++;
	sign = 0;
	if (*s == '-' || *s == '+')
		sign = 1;
	nbr_len = 0;
	while (*(s + sign + nbr_len))
	{
		if (!is_digit(*(s + sign + nbr_len)))
			return (0);
		nbr_len++;
	}
	return (nbr_len);
}
