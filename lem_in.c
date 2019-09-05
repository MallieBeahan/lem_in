/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 12:32:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/09/05 16:38:25 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		initialize(t_lemin *lemin, char **line)
{
	*line = NULL;
	lemin->is_ants = 0;
	lemin->is_start = 0;
	lemin->is_end = 0;
	lemin->number_of_ants = 0;
	lemin->count_bfs = 0;
	lemin->adjlst = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->queue = NULL;
	lemin->paths = NULL;
}

static char		parse_line(t_lemin *lemin, char *line)
{
	if (*line == ' ' || *line == '\t' || *line == '\0')
	{
		ERROR(lemin);
	}
	else if (!lemin->is_ants && ft_isnumber(line))
	{
		lemin->number_of_ants = ft_atoi(line);
		lemin->is_ants = 1;
	}
	else if (!parse_room(lemin, line))
	{
		if (lemin->adjlst)
		{
			if (!parse_link(lemin, line))
			{
				ERROR(lemin);
			}
		}
		else
		{
			ERROR(lemin);
		}
	}
	return (1);
}

static char		is_all_links_to_rooms(t_lemin *lemin)
{
	t_adjlst	*adjlst;

	if (lemin->adjlst)
	{
		adjlst = lemin->adjlst;
		while (adjlst)
		{
			if (adjlst->lst == NULL)
			{
				ERROR(lemin);
			}
			adjlst = adjlst->next;
		}
	}
	if (lemin->start == lemin->end
			|| lemin->start == NULL || lemin->end == NULL)
	{
		ERROR(lemin);
	}
	return (1);
}

static void		send_ants(t_lemin *lemin)
{
	t_path	*best_way;
	t_path	*other_ways;
	int		finished_ants;
	int		current_ant;

	finished_ants = 0;
	best_way = lemin->paths;
	current_ant = 1;
	while (finished_ants < lemin->number_of_ants)
	{
		other_ways = (lemin->paths->next ? best_way->next : NULL);
		current_ant = put_ant_to_path(lemin, best_way, current_ant);
		while (other_ways)
		{
			if (send_or_not(lemin, best_way, other_ways, current_ant))
				current_ant = put_ant_to_path(lemin, best_way, current_ant);
			other_ways = other_ways->next;
		}
		ft_printf("\n");
		do_iter(lemin);
		finished_ants = lemin->end->node.count_ants_here;
	}
}

int				main(void)
{
	char		*line;
	t_lemin		lemin;

	initialize(&lemin, &line);
	while (get_next_line(0, &line))
	{
		if (*line == '#' && *(line + 1) != '#')
		{
			free(line);
			continue ;
		}
		else if (!parse_line(&lemin, line))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	if (!is_all_links_to_rooms(&lemin))
		return (0);
	while (add_shortest_parallel_path_to_paths(&lemin))
		;
	send_ants(&lemin);
	free_graph(&lemin);
	return (0);
}
