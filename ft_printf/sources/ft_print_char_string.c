/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 23:09:56 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 19:26:09 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_char_minus(t_printf *storage, char symb)
{
	storage->b_i == MAXBUFFSIZE ? print_buff(storage) : 0;
	storage->buff[storage->b_i] = symb;
	++storage->b_i;
	++storage->len;
	if (storage->width < 2)
		return ;
	--storage->width;
	storage->zero ? write_into_buff(storage, storage->width, '0') :
	write_into_buff(storage, storage->width, ' ');
}

static void	print_char_plus(t_printf *storage, char symb)
{
	++storage->len;
	if (storage->width < 2)
	{
		storage->b_i == MAXBUFFSIZE ? print_buff(storage) : 0;
		storage->buff[storage->b_i] = symb;
		++storage->b_i;
		return ;
	}
	--storage->width;
	storage->zero ? write_into_buff(storage, storage->width, '0') :
	write_into_buff(storage, storage->width, ' ');
	storage->b_i == MAXBUFFSIZE ? print_buff(storage) : 0;
	storage->buff[storage->b_i] = symb;
	++storage->b_i;
}

static void	write_into_str(char *start, int len, t_printf *storage)
{
	int	i;

	i = 0;
	start == NULL ? start = "(null)" : 0;
	storage->len += len;
	while (len)
	{
		storage->b_i == MAXBUFFSIZE ? print_buff(storage) : 0;
		storage->buff[storage->b_i] = start[i];
		++storage->b_i;
		--len;
		++i;
	}
}

int			print_string(t_printf *storage)
{
	char	*start;
	int		len;

	start = va_arg(storage->arg, char*);
	len = start == NULL ? 6 : ft_strlen(start);
	len > storage->precision && storage->precision_status ?
	len = storage->precision : 0;
	storage->minus ? write_into_str(start, len, storage) : 0;
	if (len < storage->width)
	{
		storage->width -= len;
		!storage->zero || storage->minus ? write_into_buff(storage,
		storage->width, ' ') : write_into_buff(storage, storage->width, '0');
	}
	!storage->minus ? write_into_str(start, len, storage) : 0;
	return (1);
}

int			print_char(t_printf *storage)
{
	char symb;

	symb = va_arg(storage->arg, int);
	storage->minus ? print_char_minus(storage, symb) :
	print_char_plus(storage, symb);
	return (1);
}
