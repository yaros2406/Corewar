/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_process_indexation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <fwiley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 07:18:28 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/02 07:18:28 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process		*get_last_process(t_process *first)
{
	t_process	*last;

	if (first == NULL)
		return (NULL);
	last = first;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_process		*get_first_process(t_process *last)
{
	t_process	*first;

	if (last == NULL)
		return (NULL);
	first = last;
	while (first->prev != NULL)
		first = first->prev;
	return (first);
}
