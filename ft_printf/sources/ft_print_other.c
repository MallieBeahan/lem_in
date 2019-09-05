/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:17:36 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 19:58:42 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_other_into_buff(t_printf *storage,
t_help_struct *lst, int flag)
{
	!storage->minus ? write_into_buff(storage, lst->space, ' ') : 0;
	if (storage->sharp)
	{
		write_into_buff(storage, 1, '0');
		if (storage->type != 'o' && storage->type != 'O')
			!flag ? write_into_buff(storage, 1, 'x') :
			write_into_buff(storage, 1, 'X');
	}
	write_into_buff(storage, lst->zero, '0');
	modified_itoa(lst, storage, flag);
	storage->minus ? write_into_buff(storage, lst->space, ' ') : 0;
}

static int	space_count_x(t_printf *storage, t_help_struct *lst)
{
	unsigned char	flag;
	int				w;
	int				p;

	w = storage->width;
	p = storage->precision;
	flag = storage->type == 'o' || storage->type == 'O' ? 1 : 2;
	if (!storage->sharp && !lst->zero && storage->width > lst->len)
		return (storage->width - lst->len);
	if (storage->sharp && !lst->zero && storage->width > lst->len + flag)
		return (storage->width - lst->len - flag);
	if (!storage->sharp && w > lst->len && w > p)
		return (lst->len > p ? w - lst->len : w - p);
	if (storage->sharp && w > lst->len + flag && w > p + flag)
		return (lst->len > p ? w - lst->len - flag : w - p - flag);
	return (0);
}

static int	initialize_other(t_printf *storage, t_help_struct *lst)
{
	unsigned char	flag;
	char			p_s;
	int				p;

	p_s = storage->precision_status;
	p = storage->precision;
	flag = storage->type == 'O' || storage->type == 'o' ? 1 : 2;
	storage->type == 'p' ? storage->sharp = 1 : 0;
	(storage->type == 'O' || storage->type == 'o') &&
	!storage->precision_status && !lst->number ? storage->sharp = 0 : 0;
	if (!storage->zero)
		return (lst->number == 0 && p_s && !p ? 0 : lst->len);
	storage->minus && storage->width > lst->len &&
	storage->zero ? storage->minus = 1 : 0;
	storage->width > lst->len && !storage->precision_status
	&& !storage->sharp && !storage->minus ?
	storage->precision = storage->width : 0;
	storage->width > lst->len && !storage->precision_status &&
	storage->sharp && !storage->minus ?
	storage->precision = storage->width - flag : 0;
	return (!lst->number && storage->precision_status &&
	!storage->precision ? 0 : lst->len);
}

int			print_other(t_printf *storage,
unsigned long long int number, int flag)
{
	t_help_struct	lst;

	ft_bzero(&lst, sizeof(lst));
	!number && storage->type != 'o' && storage->type != 'O'
	? storage->sharp = 0 : 0;
	lst.base = storage->type == 'O' || storage->type == 'o' ? 8 : 16;
	lst.number = number;
	lst.len = symbs_count(number, lst.base);
	lst.len = initialize_other(storage, &lst);
	storage->precision > lst.len ? lst.zero = storage->precision - lst.len : 0;
	(storage->type == 'o' || storage->type == 'O') && storage->precision_status
	&& lst.zero > 0 && storage->sharp ? --storage->sharp : 0;
	lst.space = space_count_x(storage, &lst);
	write_other_into_buff(storage, &lst, flag);
	return (1);
}
