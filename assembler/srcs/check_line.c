/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:52:39 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 13:28:06 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "op_tab.h"
#include "asm.h"
#include "asm_error.h"

/*
**   DESCRIPTION
** The function searches for a LABEL in the file that the token points to
*/

static int		search_label(t_token *token)
{
	t_token		*tmp;

	if (!token)
		return (0);
	tmp = get_first_token(token);
	while (tmp)
	{
		if (tmp->type == T_LABEL
		&& !ft_strcmp(tmp->string_value, token->string_value))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
**   DESCRIPTION
** The function checks that the TOKEN is a valid argument for the OP operation
** under the index ARG_INDEX
**
**   COMMENT
** The function also checks the validity of the reg index, if it is a reg and
** that the label that the argument points to is in the source file
*/

static int		match_arg(t_token *token, size_t arg_index, t_op op)
{
	if (!token)
		return (0);
	if ((token->type == T_REGISTER) && (op.arg_type[arg_index] & T_REG))
	{
		if (token->digit_value < 0 || token->digit_value > 255)
			return (put_error(INVALID_REG_INDEX_ERR, token));
		return (1);
	}
	if ((token->type == T_DIRECT_LABEL || token->type == T_INDIRECT_LABEL))
	{
		if (!search_label(token))
			return (put_error(NO_LABEL_ERR, token));
	}
	if ((token->type == T_DIRECT_INT || token->type == T_DIRECT_LABEL)
	&& (op.arg_type[arg_index] & T_DIR))
		return (1);
	if ((token->type == T_INDIRECT_INT || token->type == T_INDIRECT_LABEL)
	&& (op.arg_type[arg_index] & T_IND))
		return (1);
	return (put_error(INVALID_ARG_ERR, token));
}

/*
**   DESCRIPTION
** The function checks that the arguments are valid
*/

static int		check_arg(t_token **token, t_op op)
{
	size_t		i;
	t_token		*tmp;

	tmp = *token;
	i = 0;
	while (i < op.arg_num)
	{
		if (!tmp->next || tmp->next->type == T_END_LINE)
			return (put_error(NOT_ENOUGH_ARG_ERR, tmp));
		tmp = tmp->next;
		if (!match_arg(tmp, i, op))
			return (0);
		i++;
		if (!tmp->next)
			return (put_error(NO_END_LINE_ERR, tmp));
		if (i < op.arg_num && tmp->next->type != T_SEPARATOR)
			return (put_error(NO_SEPARATOR_ERR, tmp));
		tmp = tmp->next;
	}
	if (tmp && tmp->type == T_END_LINE)
	{
		*token = tmp->next;
		return (1);
	}
	return (put_error(NO_END_LINE_ERR, tmp ? tmp->prev : NULL));
}

/*
**   DESCRIPTION
** The function checks that the line consists only of LABELS
*/

static int		is_label_line(t_token *token, t_token **first_token)
{
	if (!first_token || !*first_token)
		return (0);
	if (token && token->type == T_END_LINE)
	{
		*first_token = token->next;
		return (1);
	}
	return (0);
}

/*
**   DESCRIPTION
** The function checks the line of executable code
**
**   COMMENT
** The line is valid if:
** 1. 													END_LINE
** 2. LABEL -> 											END_LINE
** 3. 			INSTRUCTION -> 		{allowed args} ->	END_LINE
** 4. LABEL -> 	INSTRUCTION -> 		{allowed args} ->	END_LINE
*/

int				check_line(t_token **first_token)
{
	t_token		*token;
	t_op		op;

	if (!first_token || !*first_token)
		return (0);
	token = *first_token;
	if (token->type == T_END_LINE || token->type == T_COMMENT)
	{
		*first_token = (*first_token)->next;
		return (1);
	}
	if (token->type == T_LABEL)
		token = token->next;
	if (is_label_line(token, first_token))
		return (1);
	if (!token)
		return (put_error(NO_END_LINE_ERR, *first_token));
	if (token->type != T_INSTRUCTION)
		return (put_error(NO_INSTRUCTION_ERR, token));
	op = g_op_tab[token->digit_value];
	if (!check_arg(&token, op))
		return (0);
	*first_token = token;
	return (1);
}
