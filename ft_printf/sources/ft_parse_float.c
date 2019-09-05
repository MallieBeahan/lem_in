/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:53:48 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 18:56:54 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	second_round(char *str, unsigned j, double num, int i)
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

static void	rounding(t_printf *storage, t_help_struct *lst,
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
	second_round(rou, i, num, 1);
	if (rou[0] > '9')
	{
		++lst->number;
		rou[0] -= 10;
	}
	storage->precision = i;
	calc(storage, lst, flag);
	exac_float(storage, lst, flag, rou);
}

static void	ft_transform_float(t_printf *storage,
t_help_struct *lst, double num, int flag)
{
	if ((lst->number + 1) % 2 == 0)
		num >= 0.5 ? ++lst->number : 0;
	else
		num > 0.5 ? ++lst->number : 0;
	calc(storage, lst, flag);
	exac_float(storage, lst, flag, NULL);
}

int			print_float(t_printf *storage)
{
	double			num;
	t_help_struct	lst;
	int				flag;
	unsigned long	*ptr;

	ft_bzero(&lst, sizeof(lst));
	lst.base = 10;
	num = va_arg(storage->arg, double);
	if (nan_checker(storage, (long double)num))
		return (1);
	ptr = (unsigned long *)&num;
	flag = *ptr >> 63;
	num < 0 ? num = -num : 0;
	lst.number = (unsigned long int)num;
	num -= lst.number;
	storage->precision_status == 0 ? storage->precision = 6 : 0;
	storage->precision < 0 ? storage->precision = 6 : 0;
	!storage->precision ? ft_transform_float(storage, &lst, num, flag) :
	rounding(storage, &lst, num, flag);
	return (1);
}
