/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:36:24 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 20:23:37 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		int_overflow(int flag, t_printf *storage, t_help_struct *lst)
{
	if (storage->space && !lst->space && !flag &&
	!storage->plus && storage->type != 'u')
		write_into_buff(storage, 1, ' ');
	else if (lst->space > 0)
		write_into_buff(storage, lst->space, ' ');
	if (flag || (storage->plus && storage->type != 'u'))
		flag ? write_into_buff(storage, 1, '-') :
		write_into_buff(storage, 1, '+');
	write_into_buff(storage, lst->zero, '0');
	modified_itoa(lst, storage, 0);
}

static void		int_overflow_minus(int flag,
t_printf *storage, t_help_struct *lst)
{
	storage->space && !storage->plus ? write_into_buff(storage, 1, ' ') : 0;
	if (flag || (storage->plus && storage->type != 'u'))
		flag ? write_into_buff(storage, 1, '-') :
		write_into_buff(storage, 1, '+');
	write_into_buff(storage, lst->zero, '0');
	modified_itoa(lst, storage, 0);
	write_into_buff(storage, lst->space, ' ');
}

static int		space_count(t_printf *storage, int len, int flag, int zero)
{
	int w;
	int p;

	w = storage->width;
	p = storage->precision;
	if (!flag && !storage->plus && !zero && storage->width > len)
		return (storage->width - len);
	if ((flag || storage->plus) && !zero && storage->width > len + 1)
		return (--storage->width - len);
	if (!flag && !storage->plus && w > len && w > p)
		return (len > p ? w - len : w - p);
	if ((flag || storage->plus) && w > len + 1 && w > p + 1)
		return (len > p ? --w - len : --w - p);
	return (0);
}

void			int_format(t_printf *storage, t_help_struct *lst, int flag)
{
	lst->zero = storage->precision > lst->len ?
	storage->precision - lst->len : 0;
	lst->space = space_count(storage, lst->len, flag, lst->zero);
	flag ? lst->minus = 1 : 0;
	!lst->minus && storage->plus && storage->type != 'u' ? lst->plus = 1 : 0;
	storage->minus ? int_overflow_minus(flag, storage, lst) :
	int_overflow(flag, storage, lst);
}

int				change_values(t_printf *s, int len,
int flag, size_t number)
{
	s->minus && s->space && !s->zero &&
	s->width > 0 ? --s->width : 0;
	if (!s->zero)
		return (!number && s->precision_status && !s->precision ? 0 : len);
	s->minus && s->width > len ? s->minus = 1 : 0;
	s->width > len && !s->precision_status && !flag && !s->plus
	&& !s->space && !s->minus ? s->precision = s->width : 0;
	s->width > len && !s->precision_status && !flag && !s->plus
	&& s->space && s->width > 0 ? s->precision = --s->width : 0;
	s->width > len && s->precision_status == 0 && !s->minus
	&& (flag || s->plus) ? s->precision = --s->width : 0;
	return (!number && s->precision_status && !s->precision ? 0 : len);
}
