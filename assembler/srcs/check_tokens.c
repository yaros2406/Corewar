/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:54:04 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/26 13:11:11 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_error.h"
#include "asm.h"

/*
** The function checks whether there is executable code in the file
*/

static int		is_empty_file(t_token *token)
{
	while (token && (token->type == T_END_LINE || token->type == T_COMMENT
	|| token->type == T_LABEL))
		token = token->next;
	return (token ? 0 : 1);
}

/*
** FUNKCIA
** PROSTO
** RISUET
** INOPLANETYANINA
*/

static void		put_aliens(char *file_name)
{
	ft_printf("We did not find executable code in the file %s%s%s\n"
	"Maybe it was stolen by aliens.\n"
	".     .       .  .   . .   .   . .    +  .\n  .     .  :     .  "
	"  .. :. .___---------___.\n       .  .   .    .  :.:. _\".^ .^ ^.  '.. :\""
	"-_. .\n    .  :       .  .  .:../:            . .^  :.:\\.\n        .   . "
	":: +. :.:/: .   .    .        . . .:\\\n .  :    .     . _ :::/:          "
	"     .  ^ .  . .:\\\n  .. . .   . - : :.:./.                        .  .:"
	"\\\n  .      .     . :..|:                    .  .  ^. .:|\n    .       . "
	": : ..||        .                . . !:|\n  .     . . . ::. ::\\(         "
	"                  . :)/\n .   .     : . : .:.|. ######              .#####"
	"##::|\n  :.. .  :-  : .:  ::|.#######           ..########:|\n .  .  .  .."
	"  .  .. :\\ ########          :######## :/\n  .        .+ :: : -.:\\ #####"
	"###       . ########.:/\n    .  .+   . . . . :.:\\. #######       #######."
	".:/\n      :: . . . . ::.:..:.\\           .   .   ..:/\n   .   .   .  .. "
	":  -::::.\\.       | |     . .:/\n      .  :  .  .  .-:.\":.::.\\         "
	"    ..:/\n .      -.   . . . .: .:::.:.\\.           .:/\n.   .   .  :    "
	"  : ....::_:..:\\   ___.  :/\n   .   .  .   .:. .. .  .: :.:.:\\       :/"
	"\n     +   .   .   : . ::. :.:. .:.|\\  .:/|\n     .         +   .  .  ..."
	":: ..|  --.:|\n.      . . .   .  .  . ... :..:..\"(  ..)\"\n .   .       ."
	"      :  .   .: ::/  .  .::\\\nWe have already called the intergalactic "
	"%spol%sice%s\n", YELLOW, file_name, EOC, RED, BLUE, EOC);
}

/*
**   DESCRIPTION
** The function writes a string (name or comment) to the HEADER structure
**
**   COMMENT
** If the string length is longer than allowed, the function outputs an error
** and returns 0
*/

static int		write_string(char *str, t_header *header, t_token *token)
{
	size_t		max_len;
	char		*dst;

	if (!str || !header || !token)
		return (0);
	max_len = (token->type == T_CMD_NAME) ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	if (ft_strlen(str) > max_len)
		return (put_error(MAX_LEN_ERR, token));
	dst = (token->type == T_CMD_NAME) ? header->prog_name : header->comment;
	ft_strcpy(dst, str);
	return (1);
}

/*
**   DESCRIPTION
** The function checks the command line (name of comment)
**
**   COMMENT
** A line is considered valid if it is an empty string
** or CMD -> STRING -> END_LINE
*/

static int		check_line_with_cmd(t_token **token, t_header *header,
				unsigned *cmd_flag)
{
	unsigned	cmd_type;

	if (!token || !*token || !header || !cmd_flag)
		return (0);
	if ((*token)->type == T_END_LINE || (*token)->type == T_COMMENT)
	{
		*token = (*token)->next;
		return (1);
	}
	if ((*token)->type != T_CMD_NAME && (*token)->type != T_CMD_COMMENT)
		return (put_error(NO_CMD_ERR, *token));
	cmd_type = ((*token)->type == T_CMD_NAME) ? CMD_NAME : CMD_COMMENT;
	if (cmd_type & *cmd_flag)
		return (put_error(DUPLICATE_CMD_ERR, *token));
	if (!(*token)->next || !((*token)->next->type == T_STRING))
		return (put_error(NO_STRING_ERR, *token));
	if (!write_string((*token)->next->string_value, header, *token))
		return (0);
	*token = (*token)->next;
	if (!(*token)->next || (*token)->next->type != T_END_LINE)
		return (put_error(NO_END_LINE_ERR, *token));
	*token = (*token)->next;
	*cmd_flag |= cmd_type;
	return (1);
}

/*
**   DESCRIPTION
** The function checks the token sequence
**
**   COMMENT
** First the name and comment are checked then the lines are checked
** cmd_flag - flag, this flag contains information about whether the file had a
** name or comment (the CMD_NAME and CMD_COMMENT macros are used)
**
** Then the lines of executable code are checked
*/

int				check_tokens(t_token *tokens, t_header *header, char *file_name)
{
	unsigned	cmd_flag;

	if (!tokens || !header)
		return (0);
	cmd_flag = 0;
	while (tokens && (cmd_flag != (CMD_NAME | CMD_COMMENT)))
		if (!check_line_with_cmd(&tokens, header, &cmd_flag))
			return (0);
	if (cmd_flag != (CMD_NAME | CMD_COMMENT))
		return (put_error(NO_CMD_ERR, tokens));
	if (is_empty_file(tokens))
	{
		put_aliens(file_name);
		return (0);
	}
	while (tokens)
		if (!check_line(&tokens))
			return (0);
	return (1);
}
