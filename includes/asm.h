/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 15:00:42 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 14:11:08 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "op.h"

# define BUFF_READ		128

# define CMD_NAME		1
# define CMD_COMMENT	2

/*
********************************************************************************
** >>> Token types <<<
********************************************************************************
*/

enum				e_token_types
{
	T_ERROR,
	T_COMMENT,
	T_SEPARATOR,
	T_END_LINE,
	T_CMD_NAME,
	T_CMD_COMMENT,
	T_LABEL,
	T_STRING,
	T_INSTRUCTION,
	T_REGISTER,
	T_DIRECT_INT,
	T_DIRECT_LABEL,
	T_INDIRECT_INT,
	T_INDIRECT_LABEL,
};

/*
********************************************************************************
** >>> Header <<<
********************************************************************************
*/

t_header			init_header(void);

/*
********************************************************************************
** >>> Token <<<
**
**   -type
** Type of token (see more e_token_types)
**
**   -digit_value
** Value for argument token (REG, DIR, IND)
**
**   -string_value
** Value for string, label
**
**   -position
** Length of all tokens up to the current one
**
**   -line
** On which line the token is located in the source file
**
**   -prev
** Previous token
**
**   -next
** Next token
********************************************************************************
*/

typedef struct		s_token
{
	int				type;
	int				digit_value;
	char			*string_value;
	int				position;
	size_t			line;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

t_token				*init_token(int type, int digit, char *string,
					t_token *prev);

void				remove_one_token(t_token **token);

void				remove_token(t_token **token);

t_token				*get_first_token(t_token *tokens);

t_token				*get_last_token(t_token *tokens);

/*
********************************************************************************
** >>> Dynamic string <<<
**
**   -data
** Arrary with data
**
**   -mem
** Size of allocate memory
**
**   -size
** Occupied size
**
**   -i
** Pointer to the current location in the date array
**
**   -line
** Current line where the pointer is located
**
**   -row
** Current row where the pointer is located
**
**   -file_name
** File name
********************************************************************************
*/

typedef struct		s_string
{
	char			*data;
	size_t			mem;
	size_t			size;
	size_t			i;
	size_t			line;
	size_t			row;
	char			*file_name;
}					t_string;

t_string			*init_string(size_t mem);

void				remove_string(t_string **string);

int					resize_string(t_string **string, size_t new_mem_size);

void				move_str_pointer(t_string *string, size_t len);

/*
********************************************************************************
** >>> Tokenization <<<
********************************************************************************
*/

t_token				*parse_file(char *file_name);

t_string			*read_file(int fd);

t_token				*parse_from_buff(t_string *buff);

int					get_token_type(t_string *buff);

t_token				*create_token(t_string *buff, int token_type);

/*
********************************************************************************
** >>> Validation of tokens <<<
********************************************************************************
*/

int					check_tokens(t_token *tokens, t_header *header,
					char *file_name);

int					check_line(t_token **first_token);

int					set_token_size(t_token *token);

void				set_label_address(t_token *token);

void				create_binary(char *file_asm_name, t_header header,
					t_token *token);

/*
********************************************************************************
** >>> Staff <<<
********************************************************************************
*/

int					put_token(t_token *token);

void				put_line(t_token *token, char *color, int pointer);

int					put_error(int error_code, void *pointer);

int					get_arg_type(t_token *token);

size_t				is_string(char *str);

size_t				is_nbr(char *str);

int					check_zero(char *str);

void				skip_spaces(t_string *str);

#endif
