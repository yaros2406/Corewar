/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:46:17 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/29 17:35:28 by frenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**   DESCRIPTION
** Function init empty process
*/

t_process				*init_process(t_int32 r1)
{
	static t_uint32		id = 1;
	t_process			*process;
	size_t				i;

	if (!(process = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	i = 1;
	while (i <= REG_NUMBER)
		process->reg[i++] = 0;
	process->reg[1] = r1;
	process->carry = 0;
	process->pos = 0;
	process->op_code = 0;
	process->cycle_to_exe = 0;
	process->live_last_cycle = 0;
	process->live_last_id = 0;
	process->id = id++;
	process->player_id = r1 * -1;
	process->next = NULL;
	process->prev = NULL;
	return (process);
}

/*
**   DESCRIPTION
** Function copy process src
*/

t_process				*copy_process(t_process *src, t_process *prev,
						t_uint32 position)
{
	t_process			*process;
	size_t				i;

	if (!src || !(process = init_process(src->reg[1])))
		return (NULL);
	i = 1;
	while (i <= REG_NUMBER)
	{
		process->reg[i] = src->reg[i];
		i++;
	}
	process->carry = src->carry;
	process->pos = position;
	process->live_last_cycle = src->live_last_cycle;
	process->prev = prev;
	process->player_id = src->player_id;
	return (process);
}

/*
**   DESCRIPTION
** The function deletes process
*/

void					remove_one_process(t_process **list)
{
	t_process			*tmp;
	t_process			*next;
	t_process			*prev;

	if (!list || !*list)
		return ;
	tmp = *list;
	next = (*list)->next;
	prev = (*list)->prev;
	if (prev == NULL)
		*list = next;
	else
		*list = NULL;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp);
}

/*
**   DESCRIPTION
** The function deletes all processes
*/

void					remove_process(t_process **list)
{
	t_process			*prev;

	if (!list || !*list)
		return ;
	*list = get_last_process(*list);
	while (*list != NULL)
	{
		prev = (*list)->prev;
		remove_one_process(&(*list));
		*list = prev;
	}
}

/*
**   DESCRIPTION
** The function adds a process to the end of the process list and return result
*/

t_uint8					add_process(t_process **process, t_int32 reg_value)
{
	t_process			*last_process;

	if (process == NULL)
		return (FALSE);
	if (*process == NULL)
	{
		*process = init_process(reg_value);
		return (*process != NULL ? TRUE : FALSE);
	}
	last_process = get_last_process(*process);
	if (last_process != NULL)
	{
		last_process->next = init_process(reg_value);
		if (last_process->next != NULL)
		{
			last_process->next->prev = last_process;
			return (TRUE);
		}
	}
	return (FALSE);
}
