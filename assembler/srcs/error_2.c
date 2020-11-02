/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 09:10:56 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/22 06:13:10 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

void			put_no_cmd_error(t_token *token)
{
	ft_printf("Syntax error: The name and comment must be at the beginning of"
		" the file\n");
	if (!token)
		return ;
	ft_printf("@@ -1,1 +1,1 @@\n--");
	put_line(token, RED, 0);
	ft_printf("\n++%5d | %s[.name | .comment] \"....\"\n%s", token->line, GREEN,
	EOC);
}

void			put_no_end_line_error(t_token *token)
{
	t_token		*start_line;

	ft_printf("Syntax error: Line break expected\n");
	if (!token)
		return ;
	ft_printf("@@ -1,1 +1,1 @@\n--");
	if (token->next)
		put_line(token->next, RED, 0);
	else
		put_line(token, NULL, 0);
	ft_printf("\n++%5d | ", token->line);
	start_line = token;
	while (start_line && start_line->prev
		&& start_line->prev->type != T_END_LINE)
		start_line = start_line->prev;
	while (start_line != token)
	{
		put_token(start_line);
		start_line = start_line->next;
	}
	put_token(start_line);
	ft_printf("%s\\n%s\n", GREEN, EOC);
}

void			put_no_separator(t_token *token)
{
	t_token		*start_line;

	ft_printf("Syntax error: Expected separator\n");
	if (!token)
		return ;
	ft_printf("@@ -1,1 +1,1 @@\n--");
	if (token->next && token->next->type != T_END_LINE)
		put_line(token->next, RED, 0);
	else
		put_line(token, NULL, 0);
	ft_printf("\n++%5d | ", token->line);
	start_line = token;
	while (start_line && start_line->prev
		&& start_line->prev->type != T_END_LINE)
		start_line = start_line->prev;
	while (start_line != token)
	{
		put_token(start_line);
		start_line = start_line->next;
	}
	put_token(start_line);
	ft_printf("%s,%s", GREEN, EOC);
	put_arg_type(7);
}
