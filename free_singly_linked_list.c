/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_singly_linked_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:12:13 by rymuller          #+#    #+#             */
/*   Updated: 2019/08/01 16:07:37 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_lst(t_adjlst *adjlst)
{
	t_lst			*victim;
	t_lst			*buffer;

	if (adjlst && adjlst->lst)
	{
		buffer = adjlst->lst;
		while (buffer)
		{
			victim = buffer;
			buffer = victim->next;
			free(victim);
		}
		adjlst->lst = NULL;
	}
}

void			free_adjlst(t_lemin *lemin)
{
	t_adjlst		*victim;
	t_adjlst		*buffer;

	if (lemin->adjlst)
	{
		buffer = lemin->adjlst;
		while (buffer)
		{
			victim = buffer;
			buffer = victim->next;
			if (victim->node.name)
				free(victim->node.name);
			free(victim);
		}
		lemin->adjlst = NULL;
	}
}

void			free_graph(t_lemin *lemin)
{
	t_adjlst		*adjlst;

	if (lemin->adjlst)
	{
		adjlst = lemin->adjlst;
		while (adjlst)
		{
			if (adjlst->lst)
				free_lst(adjlst);
			adjlst = adjlst->next;
		}
		free_adjlst(lemin);
	}
}
