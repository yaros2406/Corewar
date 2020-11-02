/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 06:53:37 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 14:01:24 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**   DESCRIPTION
** The function return first token on sequence
*/

t_token		*get_first_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->prev)
		tokens = tokens->prev;
	return (tokens);
}

/*
**   DESCRIPTION
** The function return last token on sequence
*/

t_token		*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

/*
**   DESCRIPTION
** The function free the token
*/

void		remove_one_token(t_token **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->string_value)
		free((*token)->string_value);
	(*token)->string_value = NULL;
	(*token)->next = NULL;
	(*token)->prev = NULL;
	free(*token);
	*token = NULL;
}

/*
**   DESCRIPTION
** The function free the token sequence
*/

void		remove_token(t_token **token)
{
	t_token	*tmp;
	t_token	*next;

	if (!token || !*token)
		return ;
	tmp = get_first_token(*token);
	while (tmp)
	{
		next = tmp->next;
		remove_one_token(&tmp);
		tmp = next;
	}
	*token = NULL;
}

/*
**   DESCRIPTION
** The function сreates a new token
*/

t_token		*init_token(int type, int digit, char *string, t_token *prev)
{
	t_token	*new_token;

	if (!(new_token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	new_token->type = type;
	new_token->digit_value = digit;
	new_token->string_value = ft_strdup(string);
	new_token->position = 0;
	new_token->line = 0;
	new_token->prev = prev;
	new_token->next = NULL;
	return (new_token);
}
