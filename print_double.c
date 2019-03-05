/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:18:05 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/05 18:55:42 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <math.h>

char	*make_string(double num, t_spec *spec)
{
	t_float	*tf;
	char	*s;
	char	*str;
	char	*temp;

	num = round_p(num, spec->prec);
	tf = (t_float*)malloc(sizeof(t_float));
	tf->before_p = (int64_t)num;
	tf->after_p = num - tf->before_p;
	tf->after_p = round_p(tf->after_p, spec->prec);
	s = ft_itoa2(tf->before_p, spec);
	if (spec->prec != 0)
	{
		str = ft_strdup(s);
		free(s);
		temp = itoa_after_p(tf->after_p, spec->prec);
		s = ft_strjoin(str, temp);
		free(temp);
		free(str);
	}
	free(tf);
	return (s);
}

char	*help_string2(char *str, char *s, t_spec *spec, double num)
{
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
	return (str);
}

int		make_i(int minu, int i, int k)
{
	if (minu)
		i = k;
	else
		i--;
	return (i);
}

int		make_string2(char *s, t_spec *spec, int len, double num)
{
	char	*str;
	int		i;
	int		k;

	k = len - 1;
	len = spec->widt;
	str = ft_strnew(spec->widt);
	i = 0;
	while (i < spec->widt)
		if (spec->zero)
			str[i++] = '0';
		else
			str[i++] = ' ';
	i = make_i(spec->minu, i, k);
	while (k >= 0)
	{
		str[i] = s[k--];
		i--;
	}
	str = help_string2(str, s, spec, num);
	ft_putstr(str);
	free(str);
	free(s);
	return (len);
}

int		print_double(t_spec *spec, double num)
{
	char	*s;
	int		len;

	if (spec->prec == -1)
		spec->prec = 6;
	if (spec->plu && spec->spac)
		spec->spac = 0;
	if ((len = nan_inf_0(num, spec)))
		return (len);
	else
	{
		s = make_string(num, spec);
		len = ft_strlen(s);
	}
	if (spec->widt >= len)
	{
		if (spec->zero && spec->minu)
			spec->zero = 0;
		return (make_string2(s, spec, len, num));
	}
	ft_putstr(s);
	free(s);
	return (len);
}
