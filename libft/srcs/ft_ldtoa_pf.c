/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa_pf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 11:59:54 by Elena             #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int			clc_l(t_print *p, int *i, long double n, intmax_t d)
{
	int				l;

	l = 1;
	while ((d /= 10) >= 1)
		l++;
	*i = (p->dot) ? p->prec : 6;
	p->prec = (p->dot) ? p->prec : 6;
	p->sign = (n < 0) ? -1 : p->sign;
	*i = (p->sign || p->sp) ? *i + 1 : *i;
	*i = (p->prec == 0 && p->dot && p->hash) ? *i + 1 : *i;
	*i = (p->prec) ? *i + 1 : *i;
	*i = (p->width > l + *i) ? p->width : l + *i;
	p->width = *i;
	return (l);
}

static void			cpy_t(t_print *p, char *s, unsigned long t)
{
	int				i;
	int				j;

	i = 0;
	while (s[i] && s[i] != '.')
		i++;
	j = i;
	i = i + p->prec;
	while (i > j)
	{
		s[i--] = t % (long)10 + '0';
		t /= (long)10;
	}
}

static int			m_str(t_print *p, char *s, intmax_t d, int l)
{
	int				i;
	int				j;

	i = fill_width(p, s);
	if (p->just >= 0)
	{
		j = p->prec;
		while (j-- > 0)
			s[i--] = '0';
	}
	else
	{
		j = l;
		while (j-- > 0)
			i++;
	}
	(p->prec || p->hash) ? (s[i--] = '.') : 0;
	i = (!p->prec && !p->hash && p->just < 0) ? i - 1 : i;
	(d == 0) ? (s[i--] = '0') : 0;
	while (d)
	{
		s[i--] = d % 10 + '0';
		d /= 10;
	}
	return (i);
}

void				ft_ldtoa_pf(t_print *p, long double n)
{
	int				i;
	int				l;
	intmax_t		d;
	char			*s;
	unsigned long	t;

	i = 0;
	d = calc_d(p, n, &t);
	l = clc_l(p, &i, n, d);
	s = (char *)malloc(sizeof(char) * i + 1);
	ft_memset((void *)s, ' ', i);
	s[i] = '\0';
	i = m_str(p, s, d, l);
	i = (p->just < 0 && (p->prec || p->hash)) ? (i + 1) : i;
	est_sign(p, s, i, l);
	cpy_t(p, s, t);
	buffer(p, s, p->width);
}
