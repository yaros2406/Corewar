/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:34:48 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 10:55:54 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

/*
**   DESCRIPTION
** The function moves the string pointer as long as it points to a space
*/

void			skip_spaces(t_string *str)
{
	if (!str || !str->data)
		return ;
	while (str->data[str->i]
	&& (str->data[str->i] == ' ' || str->data[str->i] == '\t'))
		move_str_pointer(str, 1);
}

/*
**   DESCRIPTION
** The function returns the number of characters that a string occupies,
** or 0 if it is not a string
*/

size_t			is_string(char *str)
{
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_str_search(LABEL_CHARS, str[i]))
		i++;
	return (i);
}

/*
**   DESCRIPTION
** The function returns the number of characters that a number occupies,
** or 0 if it's not a number
*/

size_t			is_nbr(char *str)
{
	size_t		len;
	size_t		sign;

	if (!str)
		return (0);
	len = 0;
	sign = 0;
	if (str[len] == '+' || str[len] == '-')
		sign = 1;
	while (is_digit(str[len + sign]))
		len++;
	return (len ? len + sign : 0);
}

/*
**   DESCRIPTION
** The function return type of token
*/

int				get_arg_type(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_REGISTER)
		return (REG_CODE);
	else if (token->type == T_DIRECT_INT || token->type == T_DIRECT_LABEL)
		return (DIR_CODE);
	else if (token->type == T_INDIRECT_INT || token->type == T_INDIRECT_LABEL)
		return (IND_CODE);
	else
		return (0);
}

/*
**   DESCRIPTION
** The function returns 1 if the number is zero
*/

int				check_zero(char *str)
{
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	if (*str == '+' || *str == '-')
		i++;
	while (str[i] && is_digit(str[i]))
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}
