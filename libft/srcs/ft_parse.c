/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:09:41 by frenna            #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
** Parse specifier "dDioOuUxXfFcCsSp%"
*/

int					prs_spec(t_print *p)
{
	static t_func	f[256];
	int				i;

	f['d'] = trf_int;
	f['i'] = trf_int;
	f['D'] = trf_int;
	f['o'] = trf_oct;
	f['O'] = trf_oct;
	f['u'] = trf_uint;
	f['U'] = trf_uint;
	f['x'] = trf_hex;
	f['X'] = trf_hex;
	f['f'] = trf_double;
	f['F'] = trf_double;
	f['s'] = trf_str;
	f['S'] = trf_str;
	f['c'] = trf_char;
	f['C'] = trf_char;
	f['p'] = trf_pointer;
	f['%'] = trf_perc;
	i = f[(int)(*p->format)](p);
	p->col = *p->format;
	return (i);
}

void				p_init(t_print *p)
{
	p->just = 0;
	p->width = 0;
	p->sign = 0;
	p->deli = 0;
	p->hash = 0;
	p->sp = 0;
	p->prec = 0;
	p->dot = 0;
	p->flag = 0;
	p->cap = 0;
	p->pnt = 0;
	p->col = 0;
}

static void			fix_width_prec(t_print *p)
{
	if (p->width == -1)
	{
		p->width = (int)va_arg(p->lst, int);
		p->just = (p->width < 0) ? -1 : p->just;
		p->width = (p->width < 0) ? -p->width : p->width;
	}
	if (p->prec < 0)
		p->prec = (int)va_arg(p->lst, int);
}

int					ft_parse(t_print *p)
{
	int				i;

	i = 0;
	while (*p->format && is_valid(*p->format))
	{
		prs_flags(p);
		prs_width(p);
		prs_prec(p);
		prs_lenspec(p);
	}
	if (*p->format && !is_converse(*p->format))
	{
		buffer(p, p->format, 1);
		return (1);
	}
	if (!(*p->format))
		return (0);
	fix_width_prec(p);
	if (*p->format > 67 && *p->format < 89)
		p->cap = F_UPCASE;
	i = prs_spec(p);
	return (i);
}
