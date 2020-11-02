/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:18:28 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 10:26:53 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**   DESCRIPTION
** The function adds a token to the end of the list
*/

static void		push_to_back(t_token **dest, t_token *new_token)
{
	t_token		*last_token;

	if (!dest || !new_token)
		return ;
	if (!*dest)
	{
		*dest = new_token;
		return ;
	}
	if ((last_token = get_last_token(*dest)))
	{
		new_token->prev = last_token;
		last_token->next = new_token;
		*dest = new_token;
	}
}

/*
**   DESCRIPTION
** The function free all tokens and returns zero
*/

static t_token	*remove_tokens(t_token **token)
{
	remove_token(token);
	return (NULL);
}

/*
**   DESCRIPTION
** The function skips comments
**
**   COMMENT
** The move_str_pointer function moves the string pointer forward by the number
** passed as an argument. First, the comment character is skipped, then all
** characters are skipped until the end of the line or the end of the file is
** encountered
*/

static void		skip_comment(t_string *buff)
{
	move_str_pointer(buff, 1);
	while (buff->data[buff->i] && buff->data[buff->i] != '\n')
		move_str_pointer(buff, 1);
}

/*
**   DESCRIPTION
** The function creates a list of tokens from the buffer
*/

t_token			*parse_from_buff(t_string *buff)
{
	t_token		*tokens;
	t_token		*new_token;
	int			token_type;

	if (!buff || !buff->data)
		return (NULL);
	tokens = NULL;
	while (buff->i < buff->size)
	{
		if ((token_type = get_token_type(buff)) == T_ERROR)
			return (remove_tokens(&tokens));
		if (token_type == T_COMMENT)
			skip_comment(buff);
		else
		{
			if (!(new_token = create_token(buff, token_type)))
				return (remove_tokens(&tokens));
			push_to_back(&tokens, new_token);
		}
		skip_spaces(buff);
	}
	return (get_first_token(tokens));
}
