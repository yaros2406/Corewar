/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 07:45:43 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 11:23:10 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_tab.h"
#include "asm.h"
#include "asm_error.h"

/*
**   DESCRIPTION
** The function creates the following types of tokens:
** \n		T_END_LINE
** ,		T_SEPARATOR
*/

static t_token	*create_simple_token(t_string *buff, int token_type)
{
	t_token		*new_token;

	if (!(new_token = init_token(token_type, 0, NULL, NULL)))
		return (NULL);
	move_str_pointer(buff, 1);
	return (new_token);
}

/*
**   DESCRIPTION
** The function creates the following types of tokens:
** "string"		T_STRING
** label:		T_LABEL
** :label		T_INDIRECT_LABEL
** %:label		T_DIRECT_LABEL
**
**   COMMENT
** start - string pointer to the beginning of a string (string or label name)
** len   - string length
** At the end of the function, the dynamic string pointer is additionally moved
** by 1, if it is a STRING or LABEL, then they have one mandatory character
** after the string ("or :)
*/

static t_token	*create_string_token(t_string *buff, int token_type)
{
	size_t		start;
	size_t		len;
	t_token		*new_token;

	if (!(new_token = init_token(token_type, 0, NULL, NULL)))
		return (NULL);
	start = buff->i + ((token_type == T_STRING) ? 1 : 0);
	start += (token_type == T_INDIRECT_LABEL) ? 1 : 0;
	start += (token_type == T_DIRECT_LABEL) ? 2 : 0;
	len = 0;
	if (token_type == T_STRING)
		while (buff->data[start + len] && buff->data[start + len] != '"')
			len++;
	else
		len = is_string(buff->data + start);
	if (!(new_token->string_value = ft_strndup(buff->data + start, len)))
	{
		remove_one_token(&new_token);
		return (NULL);
	}
	move_str_pointer(buff, start + len - buff->i);
	if (token_type == T_STRING || token_type == T_LABEL)
		move_str_pointer(buff, 1);
	return (new_token);
}

/*
**   DESCRIPTION
** The function creates the following types of tokens:
** .name	T_CMD_NAME
** .comment	T_CMD_COMMENT
** fork		T_INSTRUCTION
*/

static t_token	*create_predefined_token(t_string *buff, int token_type)
{
	t_token		*new_token;
	size_t		op;
	size_t		len;

	if (!(new_token = init_token(token_type, 0, NULL, NULL)))
		return (NULL);
	if (token_type == T_CMD_NAME)
		move_str_pointer(buff, ft_strlen(NAME_CMD_STRING));
	else if (token_type == T_CMD_COMMENT)
		move_str_pointer(buff, ft_strlen(COMMENT_CMD_STRING));
	else if (token_type == T_INSTRUCTION)
	{
		op = 1;
		len = is_string(buff->data + buff->i);
		while (ft_strncmp(g_op_tab[op].name, buff->data + buff->i, len)
		&& op <= 16)
			op++;
		move_str_pointer(buff, len);
		new_token->digit_value = (int)op;
	}
	return (new_token);
}

/*
**   DESCRIPTION
** The function creates the following types of tokens:
** r1	T_REGISTER
** %23	T_DIRECT_INT
** 45	T_INDIRECT_INT
**
**   COMMENT
** start - string pointer to the beginning of a number
** len   - length of number characters, including the sign and leading zeros
** At the end of the function, the int overflow is checked. If this is a reg,
** and int overflow, the value will be assigned the invalid value -1.
*/

static t_token	*create_digit_token(t_string *buff, int token_type)
{
	t_token		*new_token;
	size_t		start;
	size_t		len;

	if (!(new_token = init_token(token_type, 0, NULL, NULL)))
		return (NULL);
	start = buff->i;
	len = 0;
	if (token_type == T_REGISTER || token_type == T_DIRECT_INT)
		start++;
	len += (size_t)is_nbr(buff->data + start);
	new_token->digit_value = ft_atoi(buff->data + start);
	if (new_token->digit_value == 0 && !check_zero(buff->data + start)
	&& token_type == T_REGISTER)
		new_token->digit_value = -1;
	move_str_pointer(buff, start + len - buff->i);
	return (new_token);
}

/*
**   DESCRIPTION
** The function creates a new token from a dynamic string and returns it
**
**   COMMENT
** The function moves the buffer string pointer to the next character after
** the token
*/

t_token			*create_token(t_string *buff, int token_type)
{
	t_token		*new_token;

	if (!buff || !buff->data)
		return (NULL);
	new_token = NULL;
	if (token_type == T_SEPARATOR || token_type == T_END_LINE)
		new_token = create_simple_token(buff, token_type);
	else if (token_type == T_STRING || token_type == T_LABEL
	|| token_type == T_INDIRECT_LABEL || token_type == T_DIRECT_LABEL)
		new_token = create_string_token(buff, token_type);
	else if (token_type == T_CMD_NAME || token_type == T_CMD_COMMENT
	|| token_type == T_INSTRUCTION)
		new_token = create_predefined_token(buff, token_type);
	else if (token_type == T_REGISTER || token_type == T_DIRECT_INT
	|| token_type == T_INDIRECT_INT)
		new_token = create_digit_token(buff, token_type);
	if (!new_token)
		put_error(ALLOC_ERR, NULL);
	else
		new_token->line = buff->line;
	return (new_token);
}
