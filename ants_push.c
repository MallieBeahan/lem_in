/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:33:08 by mbeahan           #+#    #+#             */
/*   Updated: 2019/09/04 19:12:21 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

static int ants_on_the_way(t_path *path)
{
	int counter;
	t_lst *tmp_path;

	counter = 0;
	tmp_path = path->path_lst[0];
	while(tmp_path != path->path_lst[1])
	{
		if (((t_adjlst *)tmp_path->adjlst)->node.count_ants_here)
			counter++;
		tmp_path = tmp_path->next;
	}
	return (counter);
}

static void move_ant(t_lst *hill_with_ant, t_path *path, t_lemin *lemin)
{
	if (hill_with_ant && ((t_adjlst *)hill_with_ant->adjlst)->node.count_ants_here)
	{
		if (hill_with_ant->next)
			printf("L%d-%s", ((t_adjlst *)hill_with_ant->adjlst)->node.ant_name, ((t_adjlst *)hill_with_ant->next->adjlst)->node.name);
		((t_adjlst *)hill_with_ant->adjlst)->node.count_ants_here--;
		
		if (hill_with_ant->next && (hill_with_ant->next != path->path_lst[1]))
		{
			((t_adjlst *)hill_with_ant->next->adjlst)->node.ant_name = ((t_adjlst *)hill_with_ant->adjlst)->node.ant_name;
			((t_adjlst *)hill_with_ant->next->adjlst)->node.count_ants_here++;
			((t_adjlst *)hill_with_ant->adjlst)->node.ant_name = 0;
		}
		else
		{
			if (hill_with_ant->next)
				((t_adjlst *)hill_with_ant->next->adjlst)->node.ant_name = 0;
			else
				((t_adjlst *)hill_with_ant->adjlst)->node.ant_name = 0;
			((t_adjlst *)hill_with_ant->adjlst)->node.ant_name = 0;
			lemin->end->node.count_ants_here++;
		}
	}
}

static void do_iter(t_lemin *lemin)
{
	t_path	*current_path;
	t_lst	*current_hill;
	t_lst	*hill_with_ant;
	t_lst	*stop;

	current_path = lemin->paths;
	hill_with_ant = NULL;
	while (current_path)
	{
		stop = current_path->path_lst[1];
		current_path->ants_on_the_way = ants_on_the_way(current_path);
		while (stop)
		{
			current_hill = current_path->path_lst[0];
			while (current_hill != stop && current_hill)
			{
				if (((t_adjlst *)current_hill->adjlst)->node.count_ants_here)
					hill_with_ant = current_hill;
				current_hill = current_hill->next;
			}
			move_ant(hill_with_ant, current_path, lemin);
			if (hill_with_ant && current_path->ants_on_the_way > 1)
			{
				printf(" ");
				current_path->ants_on_the_way--;
			}
			
			(stop != hill_with_ant) ? (stop = hill_with_ant) : (stop = NULL);
		}
		current_path = current_path->next;	
	}
}

static int    put_ant_to_path(t_lemin *lemin, t_path *paths, int current_ant)
{
	if (current_ant <= lemin->number_of_ants)
	{
		if (ants_on_the_way(paths) || (!(ants_on_the_way(paths)) && lemin->end->node.count_ants_here))
			printf(" ");
		//printf("%d\n", ants_on_the_way(paths));
		((t_adjlst *)paths->path_lst[0]->adjlst)->node.count_ants_here++;
		((t_adjlst *)paths->path_lst[0]->adjlst)->node.ant_name = current_ant;
		printf("L%d-%s", ((t_adjlst *)paths->path_lst[0]->adjlst)->node.ant_name, ((t_adjlst *)paths->path_lst[0]->adjlst)->node.name);
		return (current_ant + 1);
	}
	return (current_ant);
}

void    send_ants(t_lemin *lemin)
{
    t_path	*best_way;
    t_path	*other_ways;
    int		finished_ants;
	int		current_ant;

    finished_ants = 0;
    best_way = lemin->paths;
    current_ant = 1;
    while(finished_ants < lemin->number_of_ants)
    {
        (lemin->paths->next) ? (other_ways = best_way->next) : (other_ways = NULL);
        current_ant = put_ant_to_path(lemin, best_way, current_ant);
		printf("\n");
        while (other_ways)
        {
            if ((other_ways->path_len <= ((lemin->number_of_ants - current_ant) * best_way->path_len)) || (other_ways->path_len <= best_way->path_len))
                current_ant = put_ant_to_path(lemin, best_way, current_ant);
            other_ways = other_ways->next;
        }
        do_iter(lemin);
		finished_ants = lemin->end->node.count_ants_here;
    }
}