/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:56:22 by rymuller          #+#    #+#             */
/*   Updated: 2019/08/31 16:29:58 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_neighbors_adjlst_to_queue(t_lemin *lemin)
{
	t_lst		*buffer;

	buffer = ((t_adjlst *)lemin->queue->adjlst)->lst;
	while (buffer)
	{
		if (not_in_queue(lemin, buffer->adjlst))
		{
			ft_push_queue(lemin, buffer->adjlst);
			if (((t_adjlst *)buffer->adjlst)->visited_bfs == lemin->count_bfs
					&& ((t_adjlst *)lemin->queue->adjlst)->visited_pth == 0)
			{
				((t_adjlst *)buffer->adjlst)->level = \
					((t_adjlst *)lemin->queue->adjlst)->level + 1;
			}
		}
		buffer = buffer->next;
	}
}

void			breadth_first_search_to_start(t_lemin *lemin)
{
	ft_push_queue(lemin, lemin->end);
	while (lemin->queue)
	{
		if (((t_adjlst *)lemin->queue->adjlst)->visited_bfs == lemin->count_bfs
				&& ((t_adjlst *)lemin->queue->adjlst)->visited_pth == 0)
		{
			add_neighbors_adjlst_to_queue(lemin);
			((t_adjlst *)lemin->queue->adjlst)->visited_bfs = \
				lemin->count_bfs + 1;
		}
		ft_pop_queue(lemin);
	}
	lemin->count_bfs++;
}
