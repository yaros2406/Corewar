/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:06:55 by frenna            #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	put_err(char *s)
{
	while (*s && (*s == ' ' || *s == 'h'))
		s++;
	if (!*s)
		return (0);
	return (1);
}

int			ft_printf(const char *format, ...)
{
	t_print	p;

	va_start(p.lst, format);
	p.l = 0;
	p.format = (char *)format;
	init_buffer(&p, BUFF_SIZE);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			p.format++;
			if (!*p.format || !put_err(p.format))
				break ;
			p_init(&p);
			if (!ft_parse(&p))
				break ;
		}
		else
			buffer(&p, p.format, 1);
		p.format++;
	}
	va_end(p.lst);
	write(1, p.buff, p.l);
	free(p.buff);
	return (p.l);
}
