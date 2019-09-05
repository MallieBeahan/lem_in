/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_push_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:54:20 by mbeahan           #+#    #+#             */
/*   Updated: 2019/09/05 16:36:50 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		send_or_not(t_lemin *lemin, t_path *best, t_path *other, int curr_ant)
{
	if (other->path_len <= ((lemin->number_of_ants - curr_ant)
	* best->path_len))
		return (1);
	else if (other->path_len <= best->path_len)
		return (1);
	return (0);
}

t_lst	*last_ant_detect(t_lst *stop, t_lst *hill_with_ant, t_lst *current_hill)
{
	while (current_hill != stop && current_hill)
	{
		if (((t_adjlst *)current_hill->adjlst)->node.count_ants_here)
			hill_with_ant = current_hill;
		current_hill = current_hill->next;
	}
	return (hill_with_ant);
}
