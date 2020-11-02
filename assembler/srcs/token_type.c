/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 17:56:27 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 10:49:14 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "op_tab.h"
#include "asm.h"
#include "asm_error.h"

/*
**   DESCRIPTION
** The function checks whether the token type LABEL_IND, STRING, INDIRECT_LABEL
** or INSTRUCTION
**
**   COMMENT
** :label			LABEL_IND type
** label:			LABEL type
** "string"			STRING type
** fork				INSTRUCTION type
*/

static int		check_string_types(t_string *buff)
{
	size_t		str_len;
	size_t		i;
	size_t		index_op;

	if (!buff || !buff->data)
		return (T_ERROR);
	i = buff->i;
	if (buff->data[i] == LABEL_CHAR && is_string(buff->data + i + 1))
		return (T_INDIRECT_LABEL);
	if (buff->data[i] == '"' && ft_str_search(buff->data + i + 1, '"'))
		return (T_STRING);
	if (!(str_len = is_string(buff->data + i)))
		return (T_ERROR);
	if (buff->data[i + str_len] == LABEL_CHAR)
		return (T_LABEL);
	index_op = 1;
	while (index_op <= 16)
	{
		if (ft_strlen(g_op_tab[index_op].name) == str_len
		&& !ft_strncmp(buff->data + i, g_op_tab[index_op].name, str_len))
			return (T_INSTRUCTION);
		index_op++;
	}
	return (T_ERROR);
}

/*
**   DESCRIPTION
** The function checks whether the token type NAME or COMMENT
**
**   COMMENT
** .name			NAME type
** .comment			COMMENT type
*/

static int		check_cmd_type(t_string *buff)
{
	if (!buff || !buff->data || buff->data[buff->i] != '.')
		return (T_ERROR);
	if (!ft_strncmp(buff->data + buff->i, NAME_CMD_STRING,
	ft_strlen(NAME_CMD_STRING)))
		return (T_CMD_NAME);
	if (!ft_strncmp(buff->data + buff->i, COMMENT_CMD_STRING,
	ft_strlen(COMMENT_CMD_STRING)))
		return (T_CMD_COMMENT);
	return (T_ERROR);
}

/*
**   DESCRIPTION
** The function checks whether the token type DIRECT_INT or DIRECT_LABEL
**
**   COMMENT
** %123			DIRECT_INT type
** %:label		DIRECT_LABEL type
*/

static int		check_direct_type(t_string *buff)
{
	if (!buff || !buff->data || buff->data[buff->i] != DIRECT_CHAR)
		return (T_ERROR);
	if (is_nbr(buff->data + buff->i + 1))
		return (T_DIRECT_INT);
	if (buff->data[buff->i + 1] == LABEL_CHAR
	&& is_string(buff->data + buff->i + 2))
		return (T_DIRECT_LABEL);
	return (T_ERROR);
}

/*
**   DESCRIPTION
** The function adds a token to the end of the list
**
**   COMMENT
** The function does not move the buffer string pointer
*/

int				get_token_type(t_string *buff)
{
	size_t		i;
	int			token_type;

	if (!buff || !buff->data)
		return (T_ERROR);
	skip_spaces(buff);
	i = buff->i;
	if (buff->data[i] == COMMENT_CHAR || buff->data[i] == COMMENT_CHAR_ALT)
		return (T_COMMENT);
	if (buff->data[i] == SEPARATOR_CHAR)
		return (T_SEPARATOR);
	if (buff->data[i] == '\n')
		return (T_END_LINE);
	if ((token_type = check_direct_type(buff)))
		return (token_type);
	if ((token_type = check_string_types(buff)))
		return (token_type);
	if ((token_type = check_cmd_type(buff)))
		return (token_type);
	if (buff->data[i] == 'r' && is_nbr(buff->data + i + 1))
		return (T_REGISTER);
	if (is_nbr(buff->data + i))
		return (T_INDIRECT_INT);
	put_error(LEXICAL_ERR, buff);
	return (T_ERROR);
}
