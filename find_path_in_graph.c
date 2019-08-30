/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_in_graph.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:31:48 by rymuller          #+#    #+#             */
/*   Updated: 2019/08/30 18:18:59 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path		*ft_new_path_lst(t_adjlst *adjlst,
		t_lst *path_lst, int path_len)
{
	t_path			*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	path->start = adjlst;
	path->path_lst = path_lst;
	path->path_len = path_len;
	path->used = 0;
	path->next = NULL;
	return (path);
}

static t_lst		*ft_path_lst_push_back(t_lemin *lemin,
		t_lst *path_lst, t_adjlst *adjlst)
{
	t_lst			*buffer;

	if (path_lst)
	{
		buffer = path_lst;
		while (buffer->next)
			buffer = buffer->next;
		if (!(buffer->next = ft_new_lst(adjlst)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
		return (path_lst);
	}
	else
	{
		if (!(buffer = ft_new_lst(adjlst)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
		return (buffer);
	}
}

static void			ft_paths_push_back(t_lemin *lemin,
		t_lst *path_lst, int path_len)
{
	t_path			*buffer;

	if (lemin->paths)
	{
		buffer = lemin->paths;
		while (buffer->next)
			buffer = buffer->next;
		if (!(buffer->next = ft_new_path_lst(lemin->start,
						path_lst, path_len)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (!(buffer = ft_new_path_lst(lemin->start, path_lst, path_len)))
		{
			free_graph(lemin);
			exit(EXIT_FAILURE);
		}
		lemin->paths = buffer;
	}
}

static t_adjlst		*adjlst_with_min_level(t_lst *lst)
{
	t_lst		*buffer;
	t_adjlst	*adjlst;

	buffer = lst;
	adjlst = NULL;
	while (buffer)
	{
		if (((t_adjlst *)buffer->adjlst)->visited == 1)
		{
			adjlst = buffer->adjlst;
			break ;
		}
		buffer = buffer->next;
	}
	if (adjlst)
	{
		while (lst)
		{
			if (((t_adjlst *)lst->adjlst)->level < adjlst->level
					&& ((t_adjlst *)lst->adjlst)->visited == 1)
				adjlst = lst->adjlst;
			lst = lst->next;
		}
	}
	return (adjlst);
}

char				add_shortest_parallel_path_to_paths(t_lemin *lemin)
{
	t_lst		*lst;
	t_adjlst	*adjlst;
	int			path_len;
	t_lst		*path_lst;

	path_len = 0;
	path_lst = NULL;
	adjlst = lemin->start;
	if (adjlst->visited == 1)
		adjlst->visited = 2;
	while (adjlst != lemin->end)
	{
		lst = adjlst->lst;
		if (!(adjlst = adjlst_with_min_level(lst)))
		{
			free_path_lst(path_lst);
			return (0);
		}
		else
		{
			if (adjlst != lemin->end)
				adjlst->visited = 2;
			path_len++;
			path_lst = ft_path_lst_push_back(lemin, path_lst, adjlst);
		}
	}
	ft_paths_push_back(lemin, path_lst, path_len);
	return (1);
}
