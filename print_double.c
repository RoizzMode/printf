/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:18:05 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/01 14:49:09 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <math.h>

char *nan_inf_0(double num)
{
//	char *s;
	int64_t *i64;
	int i;
//	int sign;

	i64 = (int64_t *) & num;
	i = 63;
	while (i > -1)
	{
		if (*i64 & (1 << i))
			printf("1");
		else
			printf("0");
		i--;
	}
	return (NULL);
}

int print_double(t_spec *spec, double num)
{
	t_float *tf;
	char *s;
	char *str;
	int len;
	int i;
	int k;

	tf = (t_float*)malloc(sizeof(t_float));
	tf->before_p = (int64_t)num;
	tf->after_p = num - tf->before_p;
	if (spec->plu && spec->spac)
		spec->spac = 0;
	s = nan_inf_0(num);
	s = ft_itoa2(tf->before_p, spec);
	round_p(tf, spec->prec);
	if (spec->prec != 0)
		s = ft_strjoin(s, itoa_after_p(tf->after_p));
	len = ft_strlen(s);
	if (spec->widt > len)
	{
		if (spec->zero && spec->minu)
			spec->zero = 0;
		k = len - 1;
		len = spec->widt;
		str = ft_strnew(spec->widt);
		i = 0;
		while (i < spec->widt)
		{
			if (spec->zero)
				str[i++] = '0';
			else
				str[i++] = ' ';
		}
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
		if (num < 0 && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = '-';
			else
				str[spec->widt - ft_strlen(s) + 1] = '-';
		}
		if (num > 0 && spec->plu && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = '+';
			else
				str[spec->widt - ft_strlen(s) + 1] = '+';
		}
		if (num > 0 && spec->spac && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = ' ';
			else
				str[spec->widt - ft_strlen(s) + 1] = ' ';
		}
		ft_putstr(str);
		free(str);
		free(s);
		return (len);
	}
	ft_putstr(s);
	return(len);
}

int print_long_double(t_spec *spec, long double num)
{
	(void)spec;
	num = 0;
	return(0);
}
