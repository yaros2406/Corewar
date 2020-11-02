/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_synax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:43:10 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/21 09:18:43 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op_tab.h"

static int		is_arg(int type)
{
	if (type == T_REGISTER || type == T_DIRECT_INT || type == T_DIRECT_LABEL
	|| type == T_INDIRECT_INT || type == T_INDIRECT_LABEL)
		return (1);
	return (0);
}

void			put_arg_type(int arg_type)
{
	ft_printf("%s[ ", GREEN);
	if (arg_type & T_REG)
	{
		ft_printf("r[nbr] ");
		if (arg_type & T_DIR || arg_type & T_IND)
			ft_printf("%s| %s", EOC, GREEN);
	}
	if (arg_type & T_DIR)
	{
		ft_printf("%%[nbr] %s|%s %%:[label_name] ", EOC, GREEN);
		if (arg_type & T_IND)
			ft_printf("%s| %s", EOC, GREEN);
	}
	if (arg_type & T_IND)
		ft_printf("[nbr] %s|%s :[label_name] ", EOC, GREEN);
	ft_printf("%s]%s\n", GREEN, EOC);
}

void			put_few_arg(t_token *token)
{
	t_token		*instruction;
	t_op		op;
	int			arg;

	arg = 0;
	instruction = token;
	while (instruction && instruction->prev
	&& instruction->type != T_INSTRUCTION)
	{
		if (is_arg(instruction->type))
			arg++;
		instruction = instruction->prev;
	}
	if (!instruction || instruction->type != T_INSTRUCTION)
	{
		ft_printf("Syntax error: Insufficient number of arguments\n");
		return ;
	}
	op = g_op_tab[instruction->digit_value];
	ft_printf("Syntax error: The \"%s\" instruction requires %d arguments\n"
		"@@ -1,1 +1,1 @@\n--", op.name, op.arg_num);
	put_line(token, NULL, 0);
	ft_printf("\n++");
	put_line(token, GREEN, 0);
	put_arg_type(op.arg_type[arg]);
}
