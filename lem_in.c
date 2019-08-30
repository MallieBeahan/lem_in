/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 12:32:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/08/30 19:31:20 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>
#include <stdio.h>

static void		initialize(t_lemin *lemin, char **line)
{
	*line = NULL;
	lemin->is_ants = 0;
	lemin->is_start = 0;
	lemin->is_end = 0;
	lemin->number_of_ants = 0;
	lemin->adjlst = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->queue = NULL;
	lemin->paths = NULL;
}

static void		print_graph(t_lemin *lemin)
{
	t_adjlst	*buffer1;
	t_lst		*buffer2;

	printf(">>> start: name = %s, x = %d, y = %d, level = %d, visited = %d\n",
			lemin->start->node.name,
			lemin->start->node.x,
			lemin->start->node.y,
			lemin->start->level,
			lemin->start->visited);
	printf("<<< end: name = %s, x = %d, y = %d, level = %d, visited = %d\n",
			lemin->end->node.name,
			lemin->end->node.x,
			lemin->end->node.y,
			lemin->end->level,
			lemin->end->visited);
	buffer1 = lemin->adjlst;
	while (buffer1)
	{
		printf("room: name = %s, x = %d, y = %d, level = %d, visited = %d\n",
				buffer1->node.name,
				buffer1->node.x,
				buffer1->node.y,
				buffer1->level,
				buffer1->visited);
		buffer2 = buffer1->lst;
		while (buffer2)
		{
			printf("  link: name = %s, x = %d, y = %d, level = %d, visited = %d\n",
					((t_adjlst *)buffer2->adjlst)->node.name,
					((t_adjlst *)buffer2->adjlst)->node.x,
					((t_adjlst *)buffer2->adjlst)->node.y,
					((t_adjlst *)buffer2->adjlst)->level,
					((t_adjlst *)buffer2->adjlst)->visited);
			buffer2 = buffer2->next;
		}
		buffer1 = buffer1->next;
	}
}

static void		print_paths(t_lemin *lemin)
{
	t_path		*buffer1;
	t_lst		*buffer2;

	buffer1 = lemin->paths;
	while (buffer1)
	{
		printf("path: name = %s, level = %d, path_len = %d\n",
				buffer1->start->node.name,
				buffer1->start->level,
				buffer1->path_len);
		buffer2 = buffer1->path_lst;
		while (buffer2)
		{
			printf("    room: name = %s, level = %d, visited = %d\n",
					((t_adjlst *)buffer2->adjlst)->node.name,
					((t_adjlst *)buffer2->adjlst)->level,
					((t_adjlst *)buffer2->adjlst)->visited);
			buffer2 = buffer2->next;
		}
		buffer1 = buffer1->next;
	}
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

int			main(void)
{
	int		fd;
	char		*line;
	t_lemin		lemin;

	initialize(&lemin, &line);
	fd = open("hard.map", O_RDONLY);
	while (get_next_line(fd, &line))
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
	breadth_first_search_to_start(&lemin);
	print_graph(&lemin);
	printf("=================================================\n");
	while (add_shortest_parallel_path_to_paths(&lemin))
		;
	//
	print_paths(&lemin);
	send_ants(&lemin);
	printf("=================================================\n");
	free_graph(&lemin);
	return (0);
}
