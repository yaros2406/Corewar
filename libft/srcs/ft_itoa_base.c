/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 09:34:09 by Elena             #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int						fill_width(t_print *p, char *s)
{
	int					i;

	i = 0;
	if (p->just >= 0)
	{
		if (p->sp)
			s[i++] = ' ';
		while (i < p->width)
			s[i++] = (p->deli) ? '0' : ' ';
		i--;
	}
	else
	{
		if (p->sign)
			s[i++] = (p->sign > 0) ? '+' : '-';
		else if (p->sp)
			s[i++] = ' ';
	}
	return (i);
}

static int				mk(t_print *p, char *s, int b, unsigned long long n)
{
	int					j;
	int					i;

	i = fill_width(p, s);
	j = p->prec;
	while (j > 0)
	{
		s[i] = '0';
		if (((b == 16 && p->hash && n != 0) || (b == 16 && p->hash && p->pnt))
		&& ((p->just < 0 && j == p->prec - 1) || (p->just >= 0 && j == 2)))
			s[i] = 'x' - p->cap;
		i = (p->just >= 0) ? i - 1 : i + 1;
		j--;
	}
	i = (p->just >= 0) ? i + p->prec : i - 1;
	while (n)
	{
		s[i--] = ((n % (unsigned long)b) < 10) ?
		n % (unsigned long)b + '0'
		: n % (unsigned long)b + 'a' - 10 - p->cap;
		n /= (unsigned long)b;
	}
	if (i >= 0)
		s[i] = (b == 8 && p->hash) ? '0' : s[i];
	return (i);
}

static void				set_p(t_print *p, int *i, unsigned long long nb, int b)
{
	if (p->deli && p->dot && p->prec >= 0)
		p->deli = 0;
	if (p->prec < 0)
		p->prec = 0;
	*i = (p->prec > *i) ? p->prec : *i;
	p->prec = (p->prec <= *i) ? *i : p->prec;
	*i = (b == 16 && p->hash && (nb != 0 || p->pnt)) ? *i + 2 : *i;
	p->prec = (b == 16 && p->hash && (nb != 0 || p->pnt)) ?
	p->prec + 2 : p->prec;
	*i = (p->width > *i) ? p->width : *i;
	p->width = *i;
}

void					ft_itoa_b(t_print *p, unsigned long long nb, int b)
{
	int					i;
	int					l;
	unsigned long long	n;
	char				*s;

	l = (p->dot && p->prec == 0 && nb == 0) ? 0 : 1;
	n = nb;
	while ((n /= b) >= 1)
		l++;
	i = (b == 8 && p->hash && (nb != 0 || p->dot)) ? l + 1 : l;
	set_p(p, &i, nb, b);
	s = (char *)malloc(i * sizeof(char) + 1);
	ft_memset((void *)s, ' ', i);
	s[i] = '\0';
	i = mk(p, s, b, nb);
	est_sign(p, s, i, l);
	s[1] = (p->deli && b == 16 && p->hash && nb != 0) ? ('x' - p->cap) : s[1];
	buffer(p, s, p->width);
	free(s);
}
