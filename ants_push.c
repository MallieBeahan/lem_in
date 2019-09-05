/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:33:08 by mbeahan           #+#    #+#             */
/*   Updated: 2019/09/05 16:22:52 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ops(t_lst *hill_with_ant, t_path *path, int flag)
{
	if (flag == 0)
		ft_printf("L%d-%s", ((t_adjlst *)path->path_lst[0]->adjlst)->
	node.ant_name, ((t_adjlst *)path->path_lst[0]->adjlst)->node.name);
	else if (flag == 1)
		ft_printf("L%d-%s", ((t_adjlst *)hill_with_ant->adjlst)->node.ant_name,
	((t_adjlst *)hill_with_ant->next->adjlst)->node.name);
	else if (flag == 2)
		ft_printf(" ");
	else if (flag == 3)
		ft_printf("\n");
}

int		ants_on_the_way(t_path *path)
{
	t_lst	*tmp_path;
	int		counter;

	counter = 0;
	tmp_path = path->path_lst[0];
	while (tmp_path != path->path_lst[1])
	{
		if (((t_adjlst *)tmp_path->adjlst)->node.count_ants_here)
			counter++;
		tmp_path = tmp_path->next;
	}
	return (counter);
}

void	move_ant(t_lst *hill_with_ant, t_path *path, t_lemin *lemin)
{
	if (hill_with_ant && ((t_adjlst *)hill_with_ant->adjlst)->
	node.count_ants_here)
	{
		if (hill_with_ant->next)
			print_ops(hill_with_ant, path, 1);
		((t_adjlst *)hill_with_ant->adjlst)->node.count_ants_here--;
		if (hill_with_ant->next && (hill_with_ant->next != path->path_lst[1]))
		{
			((t_adjlst *)hill_with_ant->next->adjlst)->node.ant_name =
			((t_adjlst *)hill_with_ant->adjlst)->node.ant_name;
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

void	do_iter(t_lemin *lemin)
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
			hill_with_ant = last_ant_detect(stop, hill_with_ant, current_hill);
			move_ant(hill_with_ant, current_path, lemin);
			if (hill_with_ant && current_path->ants_on_the_way > 1)
			{
				print_ops(NULL, NULL, 2);
				current_path->ants_on_the_way--;
			}
			stop = (stop != hill_with_ant ? hill_with_ant : NULL);
		}
		current_path = current_path->next;
	}
}

int		put_ant_to_path(t_lemin *lemin, t_path *paths, int current_ant)
{
	if ((current_ant <= lemin->number_of_ants) &&
	(!((t_adjlst *)paths->path_lst[0]->adjlst)->node.count_ants_here))
	{
		if (ants_on_the_way(paths) || (!(ants_on_the_way(paths))
		&& lemin->end->node.count_ants_here))
			print_ops(NULL, paths, 2);
		((t_adjlst *)paths->path_lst[0]->adjlst)->node.count_ants_here++;
		((t_adjlst *)paths->path_lst[0]->adjlst)->node.ant_name = current_ant;
		print_ops(NULL, paths, 0);
		return (current_ant + 1);
	}
	return (current_ant);
}
