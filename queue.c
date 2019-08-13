/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:14:32 by rymuller          #+#    #+#             */
/*   Updated: 2019/08/13 15:01:41 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			free_queue(t_lemin *lemin)
{
	t_lst			*victim;
	t_lst			*buffer;

	if (lemin->queue)
	{
		buffer = lemin->queue;
		while (buffer)
		{
			victim = buffer;
			buffer = victim->next;
			free(victim);
		}
		lemin->queue = NULL;
	}
}

void				ft_push_queue(t_lemin *lemin, t_adjlst *adjlst)
{
	t_lst			*buffer;

	if (lemin->queue)
	{
		buffer = lemin->queue;
		while (buffer->next)
			buffer = buffer->next;
		if (!(buffer->next = ft_new_lst(adjlst)))
		{
			free_queue(lemin);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (!(buffer = ft_new_lst(adjlst)))
			exit(EXIT_FAILURE);
		lemin->queue = buffer;
	}
}

void				ft_pop_queue(t_lemin *lemin)
{
	t_lst			*buffer;

	if (lemin->queue)
	{
		buffer = lemin->queue;
		if (buffer->next)
			lemin->queue = buffer->next;
		else
			lemin->queue = NULL;
		free(buffer);
	}
}
