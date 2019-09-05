/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:38:18 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/05 17:57:50 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	wildcard(t_printf *storage, int flag)
{
	int		type;

	++storage->str;
	type = va_arg(storage->arg, int);
	if (!flag)
	{
		if (type < 0)
			return ;
		storage->precision = type;
		storage->precision_status = 1;
		return ;
	}
	if (type < 0)
	{
		type = -type;
		storage->minus = 1;
	}
	storage->width = type;
}

void		parse_precision(t_printf *storage)
{
	char	*str;
	int		precision;

	precision = 0;
	str = storage->str;
	storage->str && *storage->str == '.' ? ++storage->str : 0;
	if (storage->str && *storage->str == '*')
		return (wildcard(storage, 0));
	while (storage->str && *storage->str == '-')
	{
		++storage->str;
		storage->minus = 1;
	}
	while (storage->str && *storage->str >= '0' && *storage->str <= '9')
	{
		precision = precision * 10 + *storage->str - '0';
		++storage->str;
	}
	if (str != storage->str)
	{
		storage->precision_status = 1;
		storage->precision = precision;
	}
}

void		parse_flags(t_printf *storage)
{
	while (*storage->str && (*storage->str == '-' || *storage->str == '+'
	|| *storage->str == ' ' || *storage->str == '#' || *storage->str == '0'))
	{
		if (*storage->str == '-')
			storage->minus = 1;
		else if (*storage->str == '+')
			storage->plus = 1;
		else if (*storage->str == ' ')
			storage->space = 1;
		else if (*storage->str == '#')
			storage->sharp = 1;
		else if (*storage->str == '0')
			storage->zero = 1;
		++storage->str;
	}
}

void		parse_width(t_printf *storage)
{
	int		width;
	char	*str;

	width = 0;
	str = storage->str;
	if (storage->str && *storage->str == '*')
		return (wildcard(storage, 1));
	while (storage->str && *storage->str >= '0' && *storage->str <= '9')
	{
		width = width * 10 + *storage->str - '0';
		++storage->str;
	}
	if (str != storage->str)
		storage->width = width;
}
