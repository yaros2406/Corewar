/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 09:06:45 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 09:24:35 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		put_error_no_instruction(t_token *token)
{
	ft_printf("Syntax error: Instruction expected\n");
	if (!token)
		return ;
	put_line(token, RED, 0);
	ft_printf("\n");
}

void		put_wrong_arg(t_token *token)
{
	ft_printf("Syntax error: Invalid argument\n");
	if (!token)
		return ;
	put_line(token, RED, 1);
}

void		put_wrong_reg_index(t_token *token)
{
	ft_printf("Syntax error: Invalid register index\n");
	if (!token)
		return ;
	put_line(token, RED, 1);
}

void		put_no_search_label(t_token *token)
{
	if (!token)
	{
		ft_printf("Syntax error: Missing label in file\n");
		return ;
	}
	ft_printf("Syntax error: Missing label \"%s\" in file\n",
		token->string_value);
	put_line(token, RED, 1);
}

void		put_no_string_error(t_token *token)
{
	char	cmd[8];

	if (!token)
	{
		ft_printf("Syntax error: After the command a string was expected\n");
		return ;
	}
	ft_strcpy(cmd, token->type == T_CMD_NAME ? "name" : "comment");
	ft_printf("Syntax error: After the %s a string was expected\n", cmd);
	ft_printf("@@ -1,1 +1,1 @@\n--");
	if (token->next && token->next->type != T_END_LINE)
		put_line(token->next, RED, 0);
	else
		put_line(token, NULL, 0);
	ft_printf("\n++%5d | .%s %s\"the %s\"\n", token->line, cmd, GREEN, cmd,
			EOC);
}
