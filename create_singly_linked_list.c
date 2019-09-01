/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_singly_linked_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:11:28 by rymuller          #+#    #+#             */
/*   Updated: 2019/09/01 17:44:14 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lst				*ft_new_lst(t_adjlst *adjlst)
{
	t_lst			*lst;

	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	lst->adjlst = adjlst;
	lst->next = NULL;
	return (lst);
}

static t_adjlst		*ft_new_adjlst(t_node *node)
{
	t_adjlst		*adjlst;

	if (!(adjlst = (t_adjlst *)malloc(sizeof(t_adjlst))))
		return (NULL);
	adjlst->node.name = node->name;
	adjlst->node.x = node->x;
	adjlst->node.y = node->y;
	adjlst->node.count_ants_here = 0;
	adjlst->node.ant_name = 0;
	adjlst->lst = NULL;
	adjlst->next = NULL;
	adjlst->level = 0;
	adjlst->visited_bfs = 0;
	adjlst->visited_pth = 0;
	return (adjlst);
}

t_lst				*ft_lst_push_back(t_lemin *lemin,
		t_adjlst *adjlst1, t_adjlst *adjlst2)
{
	t_lst			*buffer;

	if (adjlst1->lst)
	{
		buffer = adjlst1->lst;
		while (buffer->next)
			buffer = buffer->next;
		if (!(buffer->next = ft_new_lst(adjlst2)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
		return (adjlst1->lst);
	}
	else
	{
		if (!(buffer = ft_new_lst(adjlst2)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
		return (buffer);
	}
}

t_adjlst			*ft_adjlst_push_back(t_lemin *lemin, t_node *node)
{
	t_adjlst		*buffer;

	if (lemin->adjlst)
	{
		buffer = lemin->adjlst;
		while (buffer->next)
			buffer = buffer->next;
		if (!(buffer->next = ft_new_adjlst(node)))
		{
			free_adjlst(lemin);
			exit(EXIT_FAILURE);
		}
		lemin->buffer = buffer->next;
		return (lemin->adjlst);
	}
	else
	{
		if (!(buffer = ft_new_adjlst(node)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
		lemin->buffer = buffer;
		return (buffer);
	}
}
