/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:55:53 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 19:19:14 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_size(t_printf *storage)
{
	unsigned lon;
	unsigned shor;

	lon = 0;
	shor = 0;
	while (*storage->str && (*storage->str == 'l' || *storage->str == 'j' ||
	*storage->str == 'h' || *storage->str == 'L' || *storage->str == 'z'))
	{
		if (*storage->str == 'l')
			lon++;
		else if (*storage->str == 'L')
			lon += 2;
		else if (*storage->str == 'j' || *storage->str == 'z')
			lon += 2;
		else if (*storage->str == 'h')
			++shor;
		++storage->str;
	}
	lon == 1 && !shor ? storage->size = 1 : 0;
	lon > 1 && !shor ? storage->size = 2 : 0;
	shor == 1 && !lon ? storage->size = 3 : 0;
	shor > 1 && !lon ? storage->size = 4 : 0;
}

int		ft_format(t_printf *storage)
{
	if (storage->type == 'c')
		return (print_char(storage));
	if (storage->type == 's')
		return (print_string(storage));
	if (storage->type == 'd' || storage->type == 'i')
		return (parse_int(storage));
	if (storage->type == 'u' || storage->type == 'U')
		return (parse_unsigned(storage));
	if (storage->type == 'x' || storage->type == 'X' || storage->type == 'p'
	|| storage->type == 'o' || storage->type == 'O')
		return (parse_other(storage));
	if (storage->type == 'f')
		return (parse_float(storage));
	return (0);
}
