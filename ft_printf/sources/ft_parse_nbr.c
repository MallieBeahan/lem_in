/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:24:05 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 19:03:46 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_int(t_printf *storage)
{
	if (!storage->size)
		return (ft_printnbr(storage, va_arg(storage->arg, int)));
	else if (storage->size == 2)
		return (ft_printnbr(storage, va_arg(storage->arg, long long int)));
	else if (storage->size == 1)
		return (ft_printnbr(storage, va_arg(storage->arg, long int)));
	else if (storage->size == 4)
		return (ft_printnbr(storage, (char)va_arg(storage->arg, unsigned int)));
	else if (storage->size == 3)
		return (ft_printnbr(storage, (short)va_arg(storage->arg, int)));
	return (0);
}

int	parse_unsigned(t_printf *storage)
{
	if (storage->type == 'U')
		return (ft_printnbr_unsigned(storage,
		va_arg(storage->arg, unsigned long int)));
	else if (!storage->size)
		return (ft_printnbr_unsigned(storage,
		va_arg(storage->arg, unsigned int)));
	else if (storage->size == 2)
		return (ft_printnbr_unsigned(storage,
		va_arg(storage->arg, unsigned long long int)));
	else if (storage->size == 1)
		return (ft_printnbr_unsigned(storage,
		va_arg(storage->arg, unsigned long int)));
	else if (storage->size == 4)
		return (ft_printnbr_unsigned(storage,
		(unsigned char)va_arg(storage->arg, int)));
	else if (storage->size == 3)
		return (ft_printnbr_unsigned(storage,
		(unsigned short)va_arg(storage->arg, int)));
		return (0);
}

int	parse_other(t_printf *storage)
{
	int	flag;

	flag = storage->type != 'p' && storage->type != 'x' && storage->type != 'o';
	if (storage->type == 'O')
		return (print_other(storage,
		va_arg(storage->arg, long long int), flag));
	else if (storage->type == 'p')
		return (print_other(storage,
		va_arg(storage->arg, unsigned long long int), flag));
	else if (!storage->size)
		return (print_other(storage,
		va_arg(storage->arg, unsigned int), flag));
	else if (storage->size == 2)
		return (print_other(storage,
		va_arg(storage->arg, long long int), flag));
	else if (storage->size == 1)
		return (print_other(storage,
		va_arg(storage->arg, long int), flag));
	else if (storage->size == 3)
		return (print_other(storage,
		(unsigned short)va_arg(storage->arg, int), flag));
	else if (storage->size == 4)
		return (print_other(storage,
		(unsigned char)va_arg(storage->arg, int), flag));
		return (0);
}

int	parse_float(t_printf *storage)
{
	if (storage->type == 'f' && (!storage->size || storage->size == 1))
		return (print_float(storage));
	if (storage->type == 'f' && storage->size == 2)
		return (print_long_float(storage));
	return (0);
}
