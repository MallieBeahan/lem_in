/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:39:38 by mbeahan           #+#    #+#             */
/*   Updated: 2019/07/08 20:23:51 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define MAXBUFFSIZE 100
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define NINF num == num + num / .0 && num < 0
# define INF num == num + num / .0 && num > 0

typedef struct	s_printf
{
	char			buff[MAXBUFFSIZE];
	unsigned int	b_i;
	int				len;
	int				width;
	int				precision;
	char			*str;
	va_list			arg;
	char			minus;
	char			plus;
	char			space;
	char			sharp;
	char			zero;
	char			precision_status;
	char			type;
	char			size;
}				t_printf;

typedef struct	s_help_struct
{
	unsigned long long int	number;
	int						space;
	int						zero;
	int						minus;
	int						plus;
	int						base;
	int						len;
}				t_help_struct;

void			print_buff(t_printf *storage);
void			write_into_buff(t_printf *storage, size_t len, char symb);
void			parse_flags(t_printf *storage);
void			parse_width(t_printf *storage);
void			parse_precision(t_printf *storage);
void			parse_size(t_printf *storage);
void			int_format(t_printf *storage, t_help_struct *lst, int flag);
void			modified_itoa(t_help_struct *lst, t_printf *storage, int flag);
void			zeroing_args(t_printf *storage);
void			ft_bzero(void *s, size_t n);
int				print_char(t_printf *storage);
int				parse_int(t_printf *storage);
int				parse_unsigned(t_printf *storage);
int				parse_other(t_printf *storage);
int				symbs_count(unsigned long long d, int base);
int				change_values(t_printf *s, int len,
				int flag, size_t number);
int				ft_printnbr_unsigned(t_printf *storage,
				unsigned long long number);
int				print_other(t_printf *storage, unsigned long long int
				number, int flag);
int				ft_format(t_printf *storage);
int				ft_printnbr(t_printf *storage, long long number);
int				print_string(t_printf *storage);
size_t			ft_strlen(const char *str);
int				ft_printf(char const *s, ...);
int				parse_float(t_printf *storage);
int				print_float(t_printf *storage);
int				print_long_float(t_printf *storage);
int				nan_checker(t_printf *storage, double num);
void			calc(t_printf *storage, t_help_struct *lst, int flag);
void			exac_float(t_printf *storage, t_help_struct *lst,
				int flag, char *rou);

#endif
