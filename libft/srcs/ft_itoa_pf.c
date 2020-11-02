/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_pf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:52:40 by Elena             #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void			est_sign(t_print *p, char *s, int i, int l)
{
	if (p->just < 0)
	{
		i = i + l + 1;
		while (i < p->width)
			s[i++] = ' ';
	}
	else
	{
		if (p->sign)
		{
			while (s[i] == '0')
				i--;
			s[i] = (p->sign > 0) ? '+' : '-';
		}
		if (p->deli)
		{
			while (i > 0)
				s[i--] = '0';
			if (p->sign)
				s[0] = (p->sign > 0) ? '+' : '-';
		}
	}
}

void			make_s(t_print *p, char *s, int l, long long nbr)
{
	int			i;
	int			j;

	i = fill_width(p, s);
	j = p->prec;
	while (j > 0)
	{
		s[i] = '0';
		i = (p->just >= 0) ? i - 1 : i + 1;
		j--;
	}
	i = (p->just >= 0) ? i + p->prec : i - 1;
	while (nbr)
	{
		s[i--] = nbr % (unsigned long)10 + '0';
		nbr /= (unsigned long)10;
	}
	est_sign(p, s, i, l);
}

static void		find_l(t_print *p, int *i, long long nbr)
{
	*i = (p->prec > *i) ? p->prec : *i;
	if (p->deli && p->dot && p->prec >= 0)
		p->deli = 0;
	if (p->prec < 0)
		p->prec = 0;
	p->prec = (p->prec <= *i) ? *i : p->prec;
	p->sign = (nbr < 0) ? -1 : p->sign;
	*i = (p->sign || p->sp) ? *i + 1 : *i;
	*i = (p->width > *i) ? p->width : *i;
	p->width = *i;
}

static void		fix_max(char *s, int n, int i)
{
	if (n == -2)
	{
		i--;
		while (s[i] != '7')
			i--;
		s[i] = '8';
	}
}

void			ft_itoa_pf(t_print *p, long long nbr)
{
	int			i;
	int			l;
	long long	n;
	char		*s;

	i = (p->dot && p->prec == 0 && nbr == 0) ? 0 : 1;
	n = (nbr < 0 && nbr != LONG_MIN) ? -1 * nbr : nbr;
	n = (nbr == LONG_MIN) ? LONG_MAX : n;
	while ((n /= 10) >= 1)
		i++;
	l = i;
	find_l(p, &i, nbr);
	s = (char *)malloc(i * sizeof(char) + 1);
	ft_memset((void *)s, ' ', i);
	s[i] = '\0';
	n = (nbr < 0) ? -1 : 1;
	n = (nbr == LONG_MIN) ? -2 : n;
	nbr = (nbr == LONG_MIN) ? LONG_MAX : nbr * n;
	make_s(p, s, l, nbr);
	fix_max(s, n, i);
	buffer(p, s, p->width);
	free(s);
}
