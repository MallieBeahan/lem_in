/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:47:19 by rymuller          #+#    #+#             */
/*   Updated: 2019/07/25 13:31:58 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char			parse_coord(char **line, t_node *node)
{
	if (**line == '\0')
		return (0);
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (ft_isnumber(*line))
		node->x = ft_atoi_shift(line);
	else
		return (0);
	if (**line == '\0')
		return (0);
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (ft_isnumber(*line))
		node->y = ft_atoi_shift(line);
	else
		return (0);
	return (1);
}

static char			is_duple_room(t_lemin *lemin, t_node *node)
{
	t_adjlst	*adjlst;

	if (lemin->adjlst)
	{
		adjlst = lemin->adjlst;
		while (adjlst)
		{
			if (!ft_strcmp(adjlst->node.name, node->name))
				return (1);
			if ((adjlst->node.x == node->x) && (adjlst->node.y == node->y))
				return (1);
			adjlst = adjlst->next;
		}
	}
	return (0);
}

static char			is_start_or_end(t_lemin *lemin, char *line)
{
	if (lemin->is_ants)
	{
		if (lemin->start == NULL)
		{
			if (!ft_strcmp("##start", line))
			{
				lemin->is_start = 1;
				return (1);
			}
		}
		if (lemin->end == NULL)
		{
			if (!ft_strcmp("##end", line))
			{
				lemin->is_end = 1;
				return (1);
			}
		}
	}
	return (0);
}

static char			add_room_to_adjlst(t_lemin *lemin, t_node *node)
{
	if (is_duple_room(lemin, node))
		return (0);
	lemin->adjlst = ft_adjlst_push_back(lemin, node);
	if (lemin->is_start)
	{
		lemin->start = lemin->buffer;
		lemin->is_start = 0;
	}
	if (lemin->is_end)
	{
		lemin->end = lemin->buffer;
		lemin->is_end = 0;
	}
	return (1);
}

char				parse_room(t_lemin *lemin, char *line)
{
	int			i;
	t_node		node;
	char		name[4096];

	if (*line == 'L' || *line == '\0')
		return (0);
	else
	{
		if (!is_start_or_end(lemin, line))
		{
			i = 0;
			while (*line && *line != ' ' && *line != '\t')
				*(name + i++) = *line++;
			*(name + i) = '\0';
			if (!parse_coord(&line, &node))
				return (0);
			if (ft_strlen(line))
				return (0);
			node.name = ft_strdup(name);
			if (!add_room_to_adjlst(lemin, &node))
				return (0);
		}
		return (1);
	}
}
