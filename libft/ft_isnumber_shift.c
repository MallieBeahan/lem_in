/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 14:58:20 by rymuller          #+#    #+#             */
/*   Updated: 2019/07/13 14:41:28 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_isnumber_shift(char **str)
{
	while (**str && !ft_isspace(**str))
	{
		if (!ft_isdigit(**str))
			return (0);
		(*str)++;
	}
	return (1);
}
