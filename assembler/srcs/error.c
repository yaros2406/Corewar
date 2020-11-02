/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 15:39:32 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/22 06:11:02 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

static void	put_lexical_error(t_string *str)
{
	char	*end_line;
	size_t	i;

	if (!str)
	{
		ft_printf("Lexical error\n");
		return ;
	}
	ft_printf("Lexical error in file <%s%s%s>\n", YELLOW, str->file_name, EOC);
	while (str->i > 0 && str->data[str->i - 1] != '\n')
		str->i--;
	if ((end_line = ft_str_search(str->data + str->i, '\n')))
		*end_line = '\0';
	ft_printf("%5zu | %.*s", str->line, (int)str->row - 1, str->data + str->i);
	ft_printf("%s%s%s\n        ", RED, str->data + str->row - 1 + str->i, EOC);
	i = 0;
	while (i < str->row - 1)
	{
		if (str->data[str->i + i++] == '\t')
			ft_printf("\t");
		else
			ft_printf(" ");
	}
	ft_printf("%s^%s\n", RED, EOC);
}

static void	put_str_len_error(t_token *token)
{
	char	cmd[8];

	if (!token)
	{
		ft_printf("Syntax error: String too long\n");
		return ;
	}
	ft_strcpy(cmd, token->type == T_CMD_NAME ? "name" : "comment");
	ft_printf("Syntax error: %s too long\n%5zu | ", cmd, token->line);
	ft_printf(".%s %s\"%s\"\n          ", cmd, RED, token->next->string_value);
	write(1, "         ", ft_strlen(cmd));
	ft_printf("^%s\n", EOC);
}

static void	put_duplicate_error(t_token *token)
{
	char	cmd[8];

	if (!token)
	{
		ft_printf("Syntax error: Duplicate command\n");
		return ;
	}
	ft_strcpy(cmd, token->type == T_CMD_NAME ? "name" : "comment");
	ft_printf("Syntax error: Duplicate %s\n", cmd);
	put_line(token, RED, 0);
	ft_printf("\n%s        ^%s\n", RED, EOC);
}

static void	put_error_syntax(int error_code, void *pointer)
{
	if (error_code == NO_END_LINE_ERR)
		put_no_end_line_error(pointer);
	else if (error_code == NO_INSTRUCTION_ERR)
		put_error_no_instruction(pointer);
	else if (error_code == INVALID_ARG_ERR)
		put_wrong_arg(pointer);
	else if (error_code == INVALID_REG_INDEX_ERR)
		put_wrong_reg_index(pointer);
	else if (error_code == NO_LABEL_ERR)
		put_no_search_label(pointer);
	else if (error_code == NOT_ENOUGH_ARG_ERR)
		put_few_arg(pointer);
	else if (error_code == NO_SEPARATOR_ERR)
		put_no_separator(pointer);
}

int			put_error(int error_code, void *pointer)
{
	if (error_code == FILE_ERR)
		ft_printf("Invalid file %s%s%s\n", YELLOW, pointer ? pointer : "", EOC);
	else if (error_code == ALLOC_ERR)
		ft_printf("Failed to allocate memory\n");
	else if (error_code == LEXICAL_ERR)
		put_lexical_error(pointer);
	else if (error_code == NO_CMD_ERR)
		put_no_cmd_error(pointer);
	else if (error_code == NO_STRING_ERR)
		put_no_string_error(pointer);
	else if (error_code == MAX_LEN_ERR)
		put_str_len_error(pointer);
	else if (error_code == DUPLICATE_CMD_ERR)
		put_duplicate_error(pointer);
	else
		put_error_syntax(error_code, pointer);
	return (0);
}
