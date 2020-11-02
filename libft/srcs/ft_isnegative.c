/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnegative.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 06:48:29 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int					ft_is_negative(char *s)
{
	unsigned char	zero;

	if (!s)
		return (0);
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		s++;
	else
		return (0);
	zero = 0;
	while (*s)
	{
		if (!is_digit(*s))
			return (0);
		zero |= (unsigned char)*s - 48;
		s++;
	}
	return (zero != 0);
}
