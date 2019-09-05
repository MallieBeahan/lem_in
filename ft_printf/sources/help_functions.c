/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:21:02 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/05 17:35:05 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_buff(t_printf *storage)
{
	write(1, storage->buff, storage->b_i);
	storage->b_i = 0;
	ft_bzero(storage->buff, MAXBUFFSIZE);
}

void		write_into_buff(t_printf *storage, size_t len, char symb)
{
	storage->len += len;
	while (len)
	{
		storage->b_i == MAXBUFFSIZE ? print_buff(storage) : 0;
		storage->buff[storage->b_i] = symb;
		--len;
		++storage->b_i;
	}
}

int			symbs_count(unsigned long long d, int base)
{
	int		count;

	count = 0;
	if (!d)
	{
		return (1);
	}
	while (d)
	{
		++count;
		d /= base;
	}
	return (count);
}

void		modified_itoa(t_help_struct *lst, t_printf *storage, int flag)
{
	char	symbol;
	int		end;

	symbol = !flag ? 'a' : 'A';
	end = lst->len + storage->b_i;
	if (end >= MAXBUFFSIZE)
	{
		print_buff(storage);
		end = lst->len;
	}
	!lst->number && lst->len > 0 ? storage->buff[storage->b_i++] = '0' : 0;
	storage->b_i = end;
	storage->len += lst->len;
	while (lst->number)
	{
		storage->buff[--end] = lst->number % lst->base < 10 ? \
		lst->number % lst->base + '0' :
			lst->number % lst->base - 10 + symbol;
		lst->number /= lst->base;
	}
}

void		zeroing_args(t_printf *storage)
{
	storage->width = 0;
	storage->precision = 0;
	storage->precision_status = 0;
	storage->type = 0;
	storage->minus = 0;
	storage->plus = 0;
	storage->space = 0;
	storage->sharp = 0;
	storage->zero = 0;
	storage->size = 0;
}
