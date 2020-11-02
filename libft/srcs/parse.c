/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elena <Elena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 10:36:50 by frenna            #+#    #+#             */
/*   Updated: 2020/06/23 16:37:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
** Parse flags "-+#0 "
*/

int		prs_flags(t_print *p)
{
	int	i;

	i = 0;
	while (is_flag(p->format[i]))
		i++;
	if (ft_strchr(p->format, '0', 0, i))
		p->deli = 1;
	if (ft_strchr(p->format, '+', 0, i))
		p->sign = 1;
	if (ft_strchr(p->format, '-', 0, i))
		p->just = -1;
	if (ft_strchr(p->format, '#', 0, i))
		p->hash = 1;
	if (ft_strchr(p->format, ' ', 0, i))
		p->sp = 1;
	if (ft_strchr(p->format, '0', 0, i) && ft_strchr(p->format, '-', 0, i))
		p->deli = 0;
	if (ft_strchr(p->format, ' ', 0, i) && ft_strchr(p->format, '+', 0, i))
		p->sp = 0;
	while (is_flag(*p->format))
		p->format++;
	return (i);
}

/*
** Parse width "<num>*" and precision flags ".*"
*/

int		prs_width(t_print *p)
{
	if (is_digit(*p->format))
	{
		p->width = ft_atoi(p->format);
		while (is_digit(*p->format))
			p->format++;
		if (*p->format == '*')
			p->format++;
	}
	else if (*p->format == '*')
	{
		p->width = -1;
		p->format++;
		if (is_digit(*p->format))
		{
			p->width = (int)va_arg(p->lst, int);
			p->width = ft_atoi(p->format);
		}
		while (is_digit(*p->format))
			p->format++;
	}
	return (1);
}

int		prs_prec(t_print *p)
{
	if (*p->format == '.')
	{
		p->dot = 1;
		p->format++;
		if (is_digit(*p->format))
		{
			p->prec = ft_atoi(p->format);
			while (is_digit(*p->format))
				p->format++;
		}
		else if (*p->format == '*')
		{
			p->format++;
			p->prec = -1;
		}
		else
			p->prec = 0;
	}
	return (1);
}

/*
** Parse length sub-specifiers "lhL"
*/

void	prs_lenspec(t_print *p)
{
	if (is_modifier(*p->format))
	{
		if (*p->format == 'h')
			p->flag = (*(p->format + 1) == 'h') ? F_SCHAR : F_SHORT;
		else if (*p->format == 'l')
			p->flag = (*(p->format + 1) == 'l') ? F_LLONG : F_LONG;
		else if (*p->format == 'L')
			p->flag = F_LLONG;
		else if (*p->format == 'j')
			p->flag = F_INTMAX;
		else if (*p->format == 'z')
			p->flag = F_SIZET;
		p->format++;
		if (*p->format == 'h' || *p->format == 'l' || *p->format == 'L')
			p->format++;
	}
}
