/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:55:33 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/21 19:19:45 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ERROR_H
# define ASM_ERROR_H

# include "asm.h"

enum		e_error
{
	FILE_ERR,
	ALLOC_ERR,
	LEXICAL_ERR,
	MAX_LEN_ERR,
	DUPLICATE_CMD_ERR,
	NO_CMD_ERR,
	NO_STRING_ERR,
	NO_END_LINE_ERR,
	NO_INSTRUCTION_ERR,
	INVALID_ARG_ERR,
	INVALID_REG_INDEX_ERR,
	NO_LABEL_ERR,
	NOT_ENOUGH_ARG_ERR,
	NO_SEPARATOR_ERR
};

void		put_error_no_instruction(t_token *token);

void		put_wrong_arg(t_token *token);

void		put_wrong_reg_index(t_token *token);

void		put_no_search_label(t_token *token);

void		put_no_string_error(t_token *token);

void		put_no_cmd_error(t_token *token);

void		put_no_end_line_error(t_token *token);

void		put_no_separator(t_token *token);

void		put_no_cmd_error(t_token *token);

void		put_no_end_line_error(t_token *token);

void		put_no_separator(t_token *token);

void		put_few_arg(t_token *token);

void		put_arg_type(int arg_type);

#endif
