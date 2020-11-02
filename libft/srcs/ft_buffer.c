/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:44:18 by frenna            #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			init_buffer(t_print *p, int l)
{
	p->buff = (char *)malloc(sizeof(char) * l);
	if (!p->buff)
		return (0);
	return (1);
}

static int	new_buff(t_print *p, int l)
{
	char	*t;

	t = (char *)malloc(sizeof(char) * (p->l + l) + 1);
	if (!t)
		return (0);
	ft_strncpy(t, p->buff, p->l);
	free(p->buff);
	p->buff = t;
	return (1);
}

void		buffer(t_print *p, char *s, int l)
{
	if (p->l + l > BUFF_SIZE)
		new_buff(p, l);
	ft_strncpy((p->buff + p->l), s, (size_t)l);
	p->l = p->l + l;
}

void		ft_putcolor(t_print *p)
{
	if (p->col == 'd' || p->col == 'D' || p->col == 'i')
		write(1, RED, 6);
	else if (p->col == 'U' || p->col == 'u')
		write(1, GREEN, 6);
	else if (p->col == 'x' || p->col == 'X')
		write(1, YELLOW, 6);
	else if (p->col == 'o' || p->col == 'O')
		write(1, BLUE, 6);
	else if (p->col == 'f' || p->col == 'F')
		write(1, MAGENTA, 6);
	else if (p->col == 'c' || p->col == 'C' || p->col == 'S'
	|| p->col == 's' || p->col == 'p')
		write(1, CYAN, 6);
	write(1, p->buff, p->l);
	if (p->col != 0)
		write(1, EOC, 5);
}
