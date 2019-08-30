/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:14:32 by rymuller          #+#    #+#             */
/*   Updated: 2019/08/30 12:57:10 by rymuller         ###   ########.fr       */
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
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (!(buffer = ft_new_lst(adjlst)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
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

char				not_in_queue(t_lemin *lemin, t_adjlst *adjlst)
{
	t_lst			*buffer;

	if (adjlst == NULL)
		return (0);
	buffer = lemin->queue;
	while (buffer)
	{
		if (adjlst == buffer->adjlst)
			return (0);
		buffer = buffer->next;
	}
	return (1);
}
