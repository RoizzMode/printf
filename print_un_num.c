/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_un_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 20:04:59 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/04 20:08:34 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *take_num(unsigned long long int num, t_spec *spec)
{
	char *s;

	if (spec->minu && spec->zero)
		spec->zero = 0;
	if (spec->type == 'o')
		s = dec_to_oct(num, spec);
	else if (spec->type == 'u')
		s = unsigned_itoa(num, spec);
	else if (spec->type == 'x')
		s = dec_to_hex(num, spec);
	else
		s = dec_to_heX(num, spec);
	return (s);
}

int	print_un_numb(t_spec *spec, unsigned long long int num)
{
	char *s;
	char *str;
	int len;
	int i = 0;
	int k;

	s = take_num(num, spec);
	len = (int)ft_strlen(s);
	if (spec->widt >= (int)ft_strlen(s))
	{
		k = len - 1;
		len = spec->widt;
		str = ft_strnew(len);
		while (i < len)
			if (spec->zero && spec->prec < 0)
				str[i++] = '0';
			else
				str[i++] = ' ';
		if (spec->minu)
			i = k;
		else
			i--;
		while (k >= 0)
		{
			str[i] = s[k];
			i--;
			k--;
		}
		if (spec->type == 'X' && spec->octo && (spec->zero || spec->minu))
		{
			str[0] = '0';
			str[1] = 'X';
		}
		if (spec->type == 'x' && spec->octo && (spec->zero || spec->minu))
		{
			str[0] = '0';
			str[1] = 'x';
		}
		ft_putstr(str);
		if (ft_strlen(s))
			free(s);
		free(str);
		return(len);
	}
	ft_putstr(s);
	if (ft_strlen(s))
		free(s);
	return (len);
}
