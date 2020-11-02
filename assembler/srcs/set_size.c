/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:52:26 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 13:52:53 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op_tab.h"

/*
**   DESCRIPTION
** The function get the size for the token
*/

static int	get_token_size(t_token *token, t_op op)
{
	if (token->type == T_REGISTER)
		return (1);
	if (token->type == T_DIRECT_INT || token->type == T_DIRECT_LABEL)
		return (op.dir_size);
	if (token->type == T_INDIRECT_INT || token->type == T_INDIRECT_LABEL)
		return (IND_SIZE);
	return (0);
}

/*
**   DESCRIPTION
** The function sets the size for each token
**
**   COMMENT
** Each token (operation, direct number, register) occupies a certain number
** of bytes in the executable code. Token position - the length of all tokens
** that go before it
*/

int			set_token_size(t_token *token)
{
	t_op	op;
	int		position_prev;

	if (!(token = get_first_token(token)))
		return (0);
	position_prev = 0;
	op = g_op_tab[0];
	while (token)
	{
		if (token->type == T_INSTRUCTION)
		{
			op = g_op_tab[token->digit_value];
			token->position = position_prev + ((op.arg_encoding) ? 2 : 1);
		}
		else
			token->position = position_prev + get_token_size(token, op);
		position_prev = token->position;
		token = token->next;
	}
	return (position_prev);
}

/*
**   DESCRIPTION
** The function returns the position that the token points to
*/

static int	get_label_position(t_token *start, t_token *target)
{
	while (start)
	{
		if (start->type == T_LABEL
		&& !ft_strcmp(start->string_value, target->string_value))
			return (start->position);
		start = start->next;
	}
	return (0);
}

/*
**   DESCRIPTION
** The function sets the position of all tokens
**
**   COMMENT
** Each token (operation, direct number, register) occupies a certain number
** of bytes in the executable code. Token position - the length of all tokens
** that go before it
*/

void		set_label_address(t_token *token)
{
	t_token	*start;
	int		label_position;
	int		instruction_position;

	if (!(start = get_first_token(token)))
		return ;
	instruction_position = 0;
	token = start;
	while (token)
	{
		if (token->type == T_INSTRUCTION && token->prev)
			instruction_position = token->prev->position;
		if (token->type == T_DIRECT_LABEL || token->type == T_INDIRECT_LABEL)
		{
			label_position = get_label_position(start, token);
			token->digit_value = label_position - instruction_position;
		}
		token = token->next;
	}
}
