/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_double3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:25:52 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:28:21 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_len_zero_long(t_spec *spec, long double num)
{
	int len;

	len = 1;
	if (spec->spac || spec->plu || read_sign(num) == 1)
		len++;
	if (spec->prec > -1)
		len += spec->prec + 1;
	return (len);
}

int		get_lenafter_zero_long(t_spec *spec)
{
	int len;

	len = 1;
	if (spec->prec > 0)
		len = spec->prec + 1;
	else
		len = 0;
	return (len);
}

char	*get_zero_s_long(t_spec *spec, long double num, int len)
{
	char	*s;
	int		i;

	s = ft_strnew(len);
	i = 0;
	while (i < len)
		s[i++] = '0';
	if (spec->spac || spec->plu || read_sign(num) == 1)
		s[2] = '.';
	else
		s[1] = '.';
	if (read_sign(num) == 1 && !((spec->minu || spec->zero) &&
				spec->widt >= (len + get_lenafter_zero_long(spec))))
		s[0] = '-';
	if (read_sign(num) == 0 && spec->plu && !((spec->minu || spec->zero)
				&& spec->widt >= (len + get_lenafter_zero_long(spec))))
		s[0] = '+';
	if (read_sign(num) == 0 && spec->spac && !((spec->minu || spec->zero)
				&& spec->widt >= (len + get_lenafter_zero_long(spec))))
		s[0] = ' ';
	return (s);
}

int		get_i_zero_long(int i, t_spec *spec, int k)
{
	if (spec->zero && spec->minu)
		spec->zero = 0;
	if (spec->minu)
		i = k;
	else
		i--;
	return (i);
}

char	*get_zero_sign_long(char *str, long double num, t_spec *spec, char *s)
{
	if (read_sign(num) == 1 && (spec->minu || spec->zero))
	{
		if (spec->minu || spec->zero)
			str[0] = '-';
		else
			str[spec->widt - ft_strlen(s) + 1] = '-';
	}
	if (read_sign(num) == 0 && spec->plu && (spec->minu || spec->zero))
	{
		if (spec->minu || spec->zero)
			str[0] = '+';
		else
			str[spec->widt - ft_strlen(s) + 1] = '+';
	}
	if (read_sign(num) == 0 && spec->spac && (spec->minu || spec->zero))
	{
		if (spec->minu || spec->zero)
			str[0] = ' ';
		else
			str[spec->widt - ft_strlen(s) + 1] = ' ';
	}
	return (str);
}
