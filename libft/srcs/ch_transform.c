/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:35:01 by Elena             #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void			put_char_pf(t_print *p, int c)
{
	char		*s;
	int			i;

	i = 1;
	i = (p->width > i) ? p->width : i;
	p->width = (p->width > i) ? p->width : i;
	s = (char *)malloc(sizeof(char) * i + 1);
	ft_memset((void *)s, ' ', i);
	s[i] = '\0';
	i = (p->just < 0 && c != 0) ? 0 : (p->width - 1);
	s[i] = (char)c;
	i = 0;
	if (p->deli)
	{
		while (i < p->width - 1)
			s[i++] = '0';
	}
	if (p->just < 0 && c == 0)
	{
		buffer(p, "\0", 1);
		buffer(p, s, (p->width - 1));
	}
	else
		buffer(p, s, p->width);
	free(s);
}

static char		*fill_s(t_print *p, char *str, int i, int l)
{
	char		*s;
	int			j;

	j = 0;
	s = (char *)malloc(sizeof(char) * i + 1);
	ft_memset((void *)s, ' ', i);
	s[i] = '\0';
	if (p->just >= 0)
	{
		while (j < i - l)
			s[j++] = (p->deli) ? '0' : ' ';
	}
	i = 0;
	while (str[i] && i < l)
		s[j++] = str[i++];
	if (p->just < 0)
	{
		while (j < p->width)
			s[j++] = ' ';
	}
	return (s);
}

static void		put_str_pf(t_print *p, char *str)
{
	char		*s;
	int			i;
	int			l;

	i = 0;
	while (str[i])
		i++;
	p->prec = (p->prec < 0) ? -p->prec : p->prec;
	i = (p->dot && i > p->prec) ? p->prec : i;
	l = i;
	i = (p->width > i) ? p->width : i;
	p->width = (p->width > i) ? p->width : i;
	s = fill_s(p, str, i, l);
	buffer(p, s, p->width);
	free(s);
}

int				trf_char(t_print *p)
{
	unsigned	c;

	if (p->flag && (p->flag == F_LLONG || p->flag == F_SHORT
	|| p->flag == F_SCHAR))
		p->flag = 0;
	if (p->sign)
		p->sign = 0;
	if (p->hash)
		p->hash = 0;
	if (!(c = va_arg(p->lst, unsigned)))
		put_char_pf(p, 0);
	else
		put_char_pf(p, c);
	return (1);
}

int				trf_str(t_print *p)
{
	unsigned	*s;

	if (p->flag && (p->flag == F_LLONG || p->flag == F_SHORT
	|| p->flag == F_SCHAR))
		p->flag = 0;
	if (p->sign)
		p->sign = 0;
	if (p->hash)
		p->hash = 0;
	if (!(s = va_arg(p->lst, unsigned*)))
		put_str_pf(p, "(null)");
	else
		put_str_pf(p, (char *)s);
	return (1);
}
