/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:54:24 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/25 20:00:15 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int				main(int ac, char **av)
{
	t_header	header;
	t_token		*tokens;

	ac--;
	av++;
	if (!ac)
		ft_printf("Usage: ./asm <sourcefile.s>\n");
	while (ac > 0)
	{
		header = init_header();
		tokens = parse_file(*av);
		if (tokens && check_tokens(tokens, &header, *av))
		{
			header.prog_size = set_token_size(tokens);
			set_label_address(tokens);
			create_binary(*av, header, tokens);
		}
		else
			ft_printf("The player from the %s%s%s file was not created\n\n",
				RED, *av, EOC);
		remove_token(&tokens);
		ac--;
		av++;
	}
	return (0);
}
