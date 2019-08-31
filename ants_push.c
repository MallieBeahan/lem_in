/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:33:08 by mbeahan           #+#    #+#             */
/*   Updated: 2019/08/31 15:50:04 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

static void move_ants(t_path *current_path, t_lst *current_hill, t_lemin *lemin)
{
	t_path	*tmp_path;
	t_lst	*tmp_hill;
	t_lst	*tmp_move;

	tmp_path = current_path;
	tmp_move = current_hill;
	while (tmp_move->next)
	{
		tmp_hill = tmp_move;
		if (((t_adjlst *)tmp_hill->next->adjlst)->node.ants_here)
		{
			while(((t_adjlst *)tmp_hill->next->adjlst)->node.ants_here && ((t_adjlst *)tmp_hill->next->adjlst) != lemin->end)
				tmp_hill = tmp_hill->next;
			if (((t_adjlst *)tmp_hill->next->adjlst) == lemin->end)
			{
				((t_adjlst *)current_hill->adjlst)->node.ant_name = 0;
				((t_adjlst *)current_hill->adjlst)->node.ants_here--;
				((t_adjlst *)current_hill->next->adjlst)->node.ants_here++;
			}
			else
			{
				((t_adjlst *)current_hill->next->adjlst)->node.ants_here++;
				((t_adjlst *)current_hill->next->adjlst)->node.ant_name = ((t_adjlst *)current_hill->adjlst)->node.ant_name;
				((t_adjlst *)current_hill->adjlst)->node.ant_name = 0;
				((t_adjlst *)current_hill->adjlst)->node.ants_here--;
			}
		}
		if (!((t_adjlst *)tmp_move->adjlst)->node.ants_here || ((t_adjlst *)tmp_move->adjlst) == lemin->end)
			tmp_move = tmp_move->next;
	}
}

static void print_used_paths(t_path *paths)
{
	t_path	*current_path;
	t_lst	*current_hill;
	char	flag;

	flag = 0;
	current_path = paths;
	while (current_path)
	{
		if (current_path->used)
		{
			current_hill = current_path->path_lst;
			while (current_hill)
			{
				if (((t_adjlst *)current_hill->adjlst)->node.ants_here && flag)
					printf(" L%d-%s", ((t_adjlst *)current_hill->adjlst)->node.ant_name, ((t_adjlst *)current_hill->adjlst)->node.name);
				else
				{
					printf("L%d-%s", ((t_adjlst *)current_hill->adjlst)->node.ant_name, ((t_adjlst *)current_hill->adjlst)->node.name);
					flag = 1;
				}
				current_hill = current_hill->next;
			}
		}
		current_path = current_path->next;
	}
	printf("\n");
}

static void do_iter(t_lemin *lemin)
{
	t_path	*current_path;
	t_lst	*current_hill;

	current_path = lemin->paths;
	while (current_path)
	{
		if (current_path->used)
		{
			current_hill = current_path->path_lst;
			while (current_hill->next)
			{
				if (((t_adjlst *)current_hill->adjlst)->node.ants_here)
					move_ants(current_path, current_hill, lemin);
				current_hill = current_hill->next;
			}
		}
	}
}

static int    put_ant_to_path(t_path *paths, int current_ant)
{
    paths->used = 1;
	((t_adjlst *)paths->path_lst->adjlst)->node.ants_here++;
	((t_adjlst *)paths->path_lst->adjlst)->node.ant_name = current_ant;
	return (current_ant + 1);
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
    while(finished_ants <= lemin->number_of_ants)
    {
        (lemin->paths->next) ? (other_ways = best_way->next) : (other_ways = NULL);
        current_ant = put_ant_to_path(best_way, current_ant);
        while (other_ways)
        {
            if ((other_ways->path_len <= ((lemin->number_of_ants - current_ant) * best_way->path_len)) || (other_ways->path_len <= best_way->path_len))
                current_ant = put_ant_to_path(other_ways, current_ant);
            other_ways = other_ways->next;
        }
        print_used_paths(lemin->paths);
        do_iter(lemin);
		finished_ants = lemin->end->node.ants_here;
    }
}