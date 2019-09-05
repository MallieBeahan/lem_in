/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_long_float.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 00:13:37 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 19:01:19 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			nan_checker(t_printf *storage, double num)
{
	char	*str;
	int		len;
	int		what;

	str = NULL;
	num != num ? str = "nan" : 0;
	NINF ? str = "-inf" : 0;
	if (INF)
		str = storage->plus ? "+inf" : "inf";
	len = str ? ft_strlen(str) : 0;
	if (len > 0)
	{
		what = storage->width - len > 0 ? storage->width - len : 0;
		!storage->minus ? write_into_buff(storage, what, ' ') : 0;
		!storage->minus && !what && storage->space && INF ?
		write_into_buff(storage, 1, ' ') : 0;
		while (*str)
		{
			write_into_buff(storage, 1, *str);
			++str;
		}
		storage->minus ? write_into_buff(storage, what, ' ') : 0;
	}
	return (str ? 1 : 0);
}

static void	round_more(char *str, unsigned j, double num, int i)
{
	int tmp;

	tmp = j;
	while (j > 0 && i == 1)
	{
		i = 0;
		if (((str[j - 1] + 1) % 2 == 0 && num >= 0.5) ||
		((str[j - 1] + 1) % 2 == 1 && num > 0.5))
		{
			str[j] = '0';
			str[j - 1] = str[j - 1] + 1;
			str[tmp] = 0;
		}
		str[j - 1] > 9 + '0' ? i = 1 : 0;
		--j;
	}
}

static void	round_long(t_printf *storage, t_help_struct *lst,
double num, int flag)
{
	char			rou[storage->precision + 1];
	unsigned		i;

	i = 0;
	ft_bzero(rou, storage->precision + 1);
	while (storage->precision)
	{
		num *= 10;
		rou[i] = (char)num + '0';
		num -= (char)num;
		++i;
		--storage->precision;
	}
	round_more(rou, i, num, 1);
	if (rou[0] > '9')
	{
		++lst->number;
		rou[0] -= 10;
	}
	storage->precision = i;
	calc(storage, lst, flag);
	exac_float(storage, lst, flag, rou);
}

static void	transform_long_float(t_printf *storage, t_help_struct *lst,
long double num, int flag)
{
	if ((lst->number + 1) % 2 == 0)
		num >= 0.5 ? ++lst->number : 0;
	else
		num > 0.5 ? ++lst->number : 0;
	calc(storage, lst, flag);
	exac_float(storage, lst, flag, NULL);
}

int			print_long_float(t_printf *storage)
{
	long double			num;
	t_help_struct		lst;
	int					flag;

	ft_bzero(&lst, sizeof(lst));
	lst.base = 10;
	flag = 0;
	num = va_arg(storage->arg, long double);
	if (num < 0)
	{
		num = -num;
		flag = 1;
	}
	lst.number = (unsigned long int)num;
	num -= lst.number;
	storage->precision_status == 0 ? storage->precision = 6 : 0;
	storage->precision < 0 ? storage->precision = 6 : 0;
	!storage->precision ? transform_long_float(storage, &lst, num, flag)
	: round_long(storage, &lst, num, flag);
	return (1);
}
