/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:10:24 by Elena             #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void			fix_pre(t_print *p, unsigned long *t, long double n, int l)
{
	long double		e;
	intmax_t		d;

	d = (n < 0) ? -1 * (intmax_t)n : (intmax_t)n;
	e = (n - (long)d) * ft_power(10, l);
	*t = (e > 0.5 && e < 1) ? 1 : *t;
	if (p->prec < 16)
		*t = (*t % 10 >= 5) ? (*t + (10 - *t % 10)) : *t;
	if (p->prec >= 16 && p->prec < 20)
	{
		*t = ((unsigned long)(e * 10) % 10 > 5) ? *t + 1 : *t;
		*t = (*t % 10 > 5) ? (*t + (10 - *t % 10)) : *t;
	}
	if (p->prec == 20)
		*t = (e - (long double)*t > 0.4) ? *t + 1 : *t;
}

intmax_t			calc_d(t_print *p, long double n, unsigned long *t)
{
	int				l;
	int				i;
	intmax_t		d;
	unsigned long	temp;

	i = (p->prec == 20) ? 1 : 0;
	d = (n < 0) ? -1 * (intmax_t)n : (intmax_t)n;
	n = (n < 0) ? -n : n;
	p->prec = (p->dot) ? p->prec : 6;
	l = (p->prec >= 20) ? 20 : p->prec + 1;
	*t = (unsigned long)((n - (long)d) * ft_power(10, l));
	fix_pre(p, t, n, l);
	temp = *t;
	while (i <= p->prec)
	{
		temp /= 10;
		i++;
	}
	d = (temp == 1) ? d + 1 : d;
	*t = (temp == 1) ? 0 : *t;
	*t = (p->prec == 20) ? *t : (*t / 10);
	return (d);
}
