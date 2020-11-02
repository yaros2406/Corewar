/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 09:16:46 by Elena             #+#    #+#             */
/*   Updated: 2020/05/06 10:47:22 by Elena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnchar(int len, char c)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char) * len + 1)))
		return ;
	s[len] = '\0';
	while (len--)
		s[len] = c;
	ft_putstr_free(s);
}
