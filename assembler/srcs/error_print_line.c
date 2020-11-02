/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:14:01 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/18 18:13:30 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op_tab.h"

static int		put_token_arg(t_token *token)
{
	if (token->type == T_REGISTER)
		return (ft_printf("r%d ", token->digit_value));
	if (token->type == T_DIRECT_INT)
		return (ft_printf("%%%d ", token->digit_value));
	if (token->type == T_DIRECT_LABEL && token->string_value)
		return (ft_printf("%%:%s ", token->string_value));
	if (token->type == T_INDIRECT_INT)
		return (ft_printf("%d ", token->digit_value));
	if (token->type == T_INDIRECT_LABEL && token->string_value)
		return (ft_printf(":%s ", token->string_value));
	return (0);
}

int				put_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_SEPARATOR)
		return (ft_printf(", "));
	if (token->type == T_END_LINE)
		return (ft_printf("\\n\n"));
	if (token->type == T_CMD_NAME)
		return (ft_printf(".name "));
	if (token->type == T_CMD_COMMENT)
		return (ft_printf(".comment "));
	if (token->type == T_STRING && token->string_value)
		return (ft_printf("\"%s\" ", token->string_value));
	if (token->type == T_LABEL)
		return (ft_printf("%s: ", token->string_value));
	if (token->type == T_INSTRUCTION && token->digit_value <= 16
	&& token->digit_value > 0)
		return (ft_printf("%s ", g_op_tab[token->digit_value].name));
	return (put_token_arg(token));
}

static void		put_pointer(int len)
{
	write(1, "\n", 1);
	while (len)
	{
		write(1, " ", 1);
		len--;
	}
	write(1, "^\n", 2);
}

void			put_line(t_token *token, char *color, int pointer)
{
	t_token		*start;
	int			len;
	int			len_token;

	if (!token)
		return ;
	start = token;
	while (start && start->prev && start->prev->type != T_END_LINE)
		start = start->prev;
	len = 0;
	len_token = ft_printf("%5d | ", token->line);
	while (start && start->type != T_END_LINE)
	{
		if (start == token || (start->next && start->next->type == T_END_LINE))
		{
			len = len ? len : len_token;
			ft_printf("%s", color ? color : "");
		}
		len_token += put_token(start);
		start = start->next;
	}
	if (pointer)
		put_pointer(len);
	ft_printf("%s", EOC);
}
