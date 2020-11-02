/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 10:34:06 by frenna            #+#    #+#             */
/*   Updated: 2020/06/30 07:54:42 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_int8	its_flag(const char *flag, char ***arg_value)
{
	if (!flag || !arg_value || !*arg_value || !**arg_value)
		return (FALSE);
	return (!ft_strcmp(**arg_value, flag));
}

static t_int8	parse_flag_debug(char ***arg_val, int *arg_count, t_game *game)
{
	char		*debug_str;
	t_uint32	debug_nbr;

	if (!ft_strncmp("-v", **arg_val, 2) && is_num((**arg_val) + 2))
	{
		game->debug_nbr = ft_atoi((**arg_val) + 2);
		game->flags |= DEBUG;
		return (1);
	}
	if (!its_flag("-v", arg_val))
		return (0);
	debug_str = *(*arg_val + 1);
	if (*arg_count <= 1 || !is_num(debug_str))
		return (0);
	debug_nbr = (t_int32)ft_atoi(debug_str);
	game->flags |= DEBUG;
	game->debug_nbr = debug_nbr;
	*arg_val += 1;
	*arg_count -= 1;
	return (1);
}

static t_int8	parse_flag_dump(char ***arg_val, int *arg_count, t_game *game)
{
	char		*dump_str;
	t_int32		dump_nbr;

	if (its_flag("-d", arg_val))
		game->dump_len = FLAG_D_LEN;
	else if (its_flag("-dump", arg_val))
		game->dump_len = FLAG_DUMP_LEN;
	else
		return (0);
	dump_str = *(*arg_val + 1);
	if (*arg_count <= 1 || !is_num(dump_str))
		return (0);
	dump_nbr = (t_int32)ft_atoi(dump_str);
	if ((dump_nbr >= 0) && !ft_is_negative(dump_str))
	{
		game->flags |= DUMP;
		game->dump_nbr = dump_nbr;
	}
	*arg_val += 1;
	*arg_count -= 1;
	return (1);
}

static t_int8	parse_flag_n(char ***arg_val, int *arg_count, t_player player[])
{
	char		*arg_id;
	char		*arg_file_name;

	if (!its_flag("-n", arg_val))
		return (0);
	if (!(arg_id = *(*arg_val + 1)))
		return (0);
	*arg_val += 1;
	*arg_count -= 1;
	if (!is_num(arg_id))
	{
		parse_file(arg_id, player, 0);
		return (1);
	}
	if (!(arg_file_name = *(*arg_val + 1)))
		return (1);
	parse_file(arg_file_name, player, (size_t)ft_atoi(arg_id));
	*arg_val += 1;
	*arg_count -= 1;
	return (1);
}

/*
**   DESCRIPTION
** The function parses the flag and writes the value to the game structure
*/

void			parse_flags(char ***arg_val, int *arg_count, t_player players[],
				t_game *game)
{
	if (its_flag("-aff", arg_val) || its_flag("-a", arg_val))
		game->flags |= AFF;
	else if (its_flag("-visual", arg_val))
		game->flags |= VISUAL;
	else if (parse_flag_dump(arg_val, arg_count, game))
		return ;
	else if (parse_flag_debug(arg_val, arg_count, game))
		return ;
	else if (parse_flag_n(arg_val, arg_count, players))
		return ;
	else
		parse_file(**arg_val, players, 0);
}
