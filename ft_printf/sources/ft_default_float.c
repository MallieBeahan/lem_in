/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:51:37 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 18:53:39 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	exac_float(t_printf *storage, t_help_struct *lst, int flag, char *rou)
{
	int norm;

	norm = rou ? ft_strlen(rou) : 0;
	lst->space ? storage->space = 0 : 0;
	!storage->minus ? write_into_buff(storage, lst->space, ' ') : 0;
	flag ? write_into_buff(storage, 1, '-') : 0;
	storage->plus ? write_into_buff(storage, 1, '+') : 0;
	storage->space && !lst->space ? write_into_buff(storage, 1, ' ') : 0;
	(lst->space > 0 || flag) && storage->precision > 0
	? --storage->precision : 0;
	write_into_buff(storage, lst->zero, '0');
	modified_itoa(lst, storage, 0);
	if (rou || storage->sharp)
		write_into_buff(storage, 1, '.');
	while (norm)
	{
		write_into_buff(storage, 1, *rou);
		++rou;
		--norm;
	}
	storage->minus ? write_into_buff(storage, lst->space, ' ') : 0;
}

void	calc(t_printf *storage, t_help_struct *lst, int flag)
{
	int check;

	flag ? storage->plus = 0 : 0;
	storage->plus || flag ? storage->space = 0 : 0;
	lst->len = symbs_count(lst->number, 10);
	storage->precision > 0 ? ++storage->precision : 0;
	check = lst->len + storage->precision;
	!storage->precision && storage->sharp ? ++check : 0;
	flag || storage->plus || (storage->space && !storage->plus &&
	storage->zero && storage->width > check) ? ++check : 0;
	storage->minus ? storage->zero = 0 : 0;
	!storage->zero && storage->width > check ?
	lst->space = storage->width - check : 0;
	storage->zero && storage->width > check ?
	lst->zero = storage->width - check : 0;
}
