/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:27:12 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 19:15:36 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printnbr_unsigned(t_printf *s, unsigned long long number)
{
	int				flag;
	t_help_struct	lst;

	flag = 0;
	ft_bzero(&lst, sizeof(lst));
	lst.number = number;
	lst.len = change_values(s, symbs_count(lst.number, 10), flag, lst.number);
	lst.base = 10;
	int_format(s, &lst, flag);
	return (1);
}

int		ft_printnbr(t_printf *s, long long number)
{
	t_help_struct	lst;
	int				flag;

	flag = 0;
	ft_bzero(&lst, sizeof(lst));
	if (number < 0)
	{
		lst.number = -number;
		flag = 1;
		s->space = 0;
	}
	else
		lst.number = number;
	lst.len = change_values(s, symbs_count(lst.number, 10), flag, lst.number);
	lst.base = 10;
	int_format(s, &lst, flag);
	return (1);
}
