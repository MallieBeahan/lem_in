/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:55:08 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 20:02:29 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_string(t_printf *storage)
{
	parse_flags(storage);
	parse_width(storage);
	parse_width(storage);
	parse_precision(storage);
	parse_precision(storage);
	parse_flags(storage);
	parse_size(storage);
	parse_flags(storage);
	storage->type = *storage->str;
	if (storage->type)
	{
		ft_format(storage) ? 0 : write_into_buff(storage, 1, *storage->str);
		++storage->str;
		zeroing_args(storage);
	}
}

static void	percent_check(t_printf *storage)
{
	int	count;

	count = 0;
	while (*storage->str && *storage->str == '%')
	{
		++storage->str;
		count++;
	}
	if (count % 2 == 0)
	{
		write_into_buff(storage, count / 2, '%');
		return ;
	}
	count = (count - 1) / 2;
	write_into_buff(storage, count, '%');
	parse_string(storage);
}

static void	write_into_storage(t_printf *storage)
{
	while (*storage->str && *storage->str != '%')
	{
		storage->b_i == MAXBUFFSIZE ? print_buff(storage) : 0;
		storage->buff[storage->b_i] = *storage->str;
		storage->b_i++;
		++storage->str;
		++storage->len;
	}
}

int			ft_printf(char const *s, ...)
{
	t_printf storage;

	ft_bzero(&storage, sizeof(storage));
	storage.str = (char *)s;
	va_start(storage.arg, s);
	while (*storage.str)
	{
		write_into_storage(&storage);
		percent_check(&storage);
	}
	write(1, storage.buff, storage.b_i);
	va_end(storage.arg);
	return (storage.len);
}
