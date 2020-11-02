/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:00:42 by Elena             #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int						trf_int(t_print *p)
{
	long long			n;

	if (p->hash)
		p->hash = 0;
	if (p->flag && p->flag == F_LONG)
		n = (long long)va_arg(p->lst, long);
	else if (p->flag && p->flag == F_LLONG)
		n = (long long)va_arg(p->lst, long long);
	else if (p->flag && p->flag == F_SHORT)
		n = (long long)((short)va_arg(p->lst, int));
	else if (p->flag && p->flag == F_SCHAR)
		n = (long long)((char)va_arg(p->lst, int));
	else if (p->flag && p->flag == F_INTMAX)
		n = (long long)va_arg(p->lst, intmax_t);
	else if (p->flag && p->flag == F_SIZET)
		n = (long long)va_arg(p->lst, ssize_t);
	else
		n = (long long)va_arg(p->lst, int);
	ft_itoa_pf(p, n);
	return (1);
}

int						trf_uint(t_print *p)
{
	unsigned long long	n;

	if (p->hash)
		p->hash = 0;
	if (p->sign)
		p->sign = 0;
	if (p->sp)
		p->sp = 0;
	if ((p->flag && p->flag == F_LONG) || p->cap)
		n = (unsigned long long)va_arg(p->lst, unsigned long);
	else if (p->flag && p->flag == F_LLONG)
		n = (unsigned long long)va_arg(p->lst, unsigned long long);
	else if (p->flag && p->flag == F_SHORT)
		n = (unsigned long long)(va_arg(p->lst, unsigned long long));
	else if (p->flag && p->flag == F_SCHAR)
		n = (unsigned long long)((unsigned char)va_arg(p->lst, int));
	else if (p->flag && p->flag == F_INTMAX)
		n = (unsigned long long)va_arg(p->lst, uintmax_t);
	else if (p->flag && p->flag == F_SIZET)
		n = (unsigned long long)va_arg(p->lst, ssize_t);
	else
		n = (unsigned long long)va_arg(p->lst, unsigned int);
	ft_utoa_pf(p, n);
	return (1);
}

int						trf_oct(t_print *p)
{
	unsigned long long	u;

	if (p->sign)
		p->sign = 0;
	if (p->sp)
		p->sp = 0;
	if (p->flag && p->flag == F_LONG)
		u = (unsigned long)va_arg(p->lst, unsigned long);
	else if (p->flag && p->flag == F_LLONG)
		u = (unsigned long long)va_arg(p->lst, unsigned long long);
	else if (p->flag && p->flag == F_SHORT)
		u = (unsigned long)((unsigned short)va_arg(p->lst, int));
	else if (p->flag && p->flag == F_SCHAR)
		u = (unsigned long)((unsigned char)va_arg(p->lst, int));
	else if (p->flag && p->flag == F_INTMAX)
		u = (unsigned long long)va_arg(p->lst, uintmax_t);
	else if (p->flag && p->flag == F_SIZET)
		u = (unsigned long long)va_arg(p->lst, ssize_t);
	else
		u = (unsigned long)va_arg(p->lst, unsigned int);
	ft_itoa_b(p, u, 8);
	return (1);
}

int						trf_hex(t_print *p)
{
	unsigned long long	u;

	if (p->sign)
		p->sign = 0;
	if (p->sp)
		p->sp = 0;
	if (p->flag && p->flag == F_LONG)
		u = (unsigned long)va_arg(p->lst, unsigned long);
	else if (p->flag && p->flag == F_LLONG)
		u = (unsigned long long)va_arg(p->lst, unsigned long long);
	else if (p->flag && p->flag == F_SHORT)
		u = (unsigned long)((unsigned short)va_arg(p->lst, int));
	else if (p->flag && p->flag == F_SCHAR)
		u = (unsigned long)((unsigned char)va_arg(p->lst, int));
	else if (p->flag && p->flag == F_INTMAX)
		u = (unsigned long long)va_arg(p->lst, uintmax_t);
	else if (p->flag && p->flag == F_SIZET)
		u = (unsigned long long)va_arg(p->lst, ssize_t);
	else
		u = (unsigned long)va_arg(p->lst, unsigned int);
	ft_itoa_b(p, u, 16);
	return (1);
}

int						trf_double(t_print *p)
{
	long double			n;

	if (p->flag && p->flag == F_LLONG)
		n = (long double)va_arg(p->lst, long double);
	else if (p->flag && p->flag == F_LONG)
		n = (long double)va_arg(p->lst, double);
	else
		n = (long double)va_arg(p->lst, double);
	ft_ldtoa_pf(p, n);
	return (1);
}
