/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 10:18:45 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 14:15:55 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_tab.h"
#include "asm.h"
#include "asm_error.h"

/*
**   DESCRIPTION
** This function creates a file with the .cor extension. If the file didn't have
** an extension (for example, file), create a file file.com
*/

static char	*get_file_cor_name(char *file_asm_name)
{
	size_t	i;
	char	*file_cor_name;

	i = ft_strlen(file_asm_name) - 1;
	while (file_asm_name[i] != '.')
	{
		if (i == 0 || file_asm_name[i] == '/')
		{
			i = ft_strlen(file_asm_name);
			break ;
		}
		i--;
	}
	if (!(file_cor_name = (char *)malloc(sizeof(char) * (i + 5))))
	{
		put_error(ALLOC_ERR, NULL);
		return (NULL);
	}
	ft_str_n_copy(file_cor_name, file_asm_name, i);
	ft_str_n_copy(file_cor_name + i, ".cor", 4);
	return (file_cor_name);
}

/*
**   DESCRIPTION
** The function writes the digit to a file
*/

static void	write_digit(int fd, unsigned int digit, size_t size)
{
	char	c;

	if (!size)
		return ;
	size--;
	c = (digit >> (size * 8)) & 0xFF;
	write(fd, &c, 1);
	write_digit(fd, digit, size);
}

/*
**   DESCRIPTION
** The function writes the instruction (instruction code and encoding byte)
** to a file
*/

static void	write_instruction(int fd, t_token *instruction)
{
	t_token			*token;
	unsigned char	encoding_byte;
	unsigned int	type;
	size_t			i;

	write_digit(fd, instruction->digit_value, 1);
	if (g_op_tab[instruction->digit_value].arg_encoding == 0)
		return ;
	token = instruction->next;
	encoding_byte = 0;
	i = 0;
	while (i < g_op_tab[instruction->digit_value].arg_num && token)
	{
		if ((type = get_arg_type(token)))
		{
			encoding_byte |= type << (6 - 2 * i);
			i++;
		}
		token = token->next;
	}
	write_digit(fd, encoding_byte, 1);
}

/*
**   DESCRIPTION
** The function writes the source code to a file
*/

static void	write_executable_code(int fd, t_token *token)
{
	t_op	op;

	token = get_first_token(token);
	while (token)
	{
		if (token->type == T_INSTRUCTION)
		{
			write_instruction(fd, token);
			op = g_op_tab[token->digit_value];
		}
		else if (token->type == T_REGISTER)
			write_digit(fd, token->digit_value, 1);
		else if (token->type == T_DIRECT_INT || token->type == T_DIRECT_LABEL)
			write_digit(fd, token->digit_value, op.dir_size);
		else if (token->type == T_INDIRECT_INT
		|| token->type == T_INDIRECT_LABEL)
			write_digit(fd, token->digit_value, 2);
		token = token->next;
	}
}

/*
**   DESCRIPTION
** The function creates a binary file and writes the name, comment from token,
** and source code from token
*/

void		create_binary(char *file_asm_name, t_header header, t_token *token)
{
	int		fd;
	char	*file_cor_name;

	if (!file_asm_name || !token)
		return ;
	if (!(file_cor_name = get_file_cor_name(file_asm_name)))
		return ;
	if ((fd = open(file_cor_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) <= 0)
	{
		ft_printf("%sPermission denied%s. The %s%s%s file was not created\n",
		RED, EOC, YELLOW, file_cor_name, EOC);
		free(file_cor_name);
		return ;
	}
	write_digit(fd, header.magic, 4);
	write(fd, header.prog_name, PROG_NAME_LENGTH);
	write(fd, "\0\0\0\0", 4);
	write_digit(fd, header.prog_size, 4);
	write(fd, header.comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
	write_executable_code(fd, token);
	ft_printf("%s✓%s Write output program to %s%s%s\n", GREEN, EOC, YELLOW,
		file_cor_name, EOC);
	free(file_cor_name);
	close(fd);
}
