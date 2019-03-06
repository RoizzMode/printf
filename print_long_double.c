/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:55:57 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:29:40 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_s_long(long double num, t_spec *spec)
{
	char		*s;
	char		*str;
	char		*temp;
	t_dfloat	*tf;

	num = round_p_long(num, spec->prec);
	tf = (t_dfloat*)malloc(sizeof(t_dfloat));
	tf->before_p = (int64_t)num;
	tf->after_p = num - tf->before_p;
	tf->after_p = round_p_long(tf->after_p, spec->prec);
	s = ft_itoa2(tf->before_p, spec);
	if (spec->prec != 0)
	{
		str = ft_strdup(s);
		temp = itoa_after_p_long(tf->after_p, spec->prec);
		free(s);
		s = ft_strjoin(str, temp);
		free(str);
		free(temp);
		free(tf);
	}
	return (s);
}

void	change_spec_long(t_spec *spec)
{
	if (spec->prec == -1)
		spec->prec = 6;
	if (spec->plu && spec->spac)
		spec->spac = 0;
	if (spec->minu && spec->zero)
		spec->zero = 0;
}

char	*get_str_widt_long(t_spec *spec, char *s, int len)
{
	char	*str;
	int		k;
	int		i;

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
		str[i] = s[k--];
		i--;
	}
	return (str);
}

char	*get_str_sign_long(t_spec *spec, char *str, char *s, long double num)
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

int		print_long_double(t_spec *spec, long double num)
{
	char	*s;
	char	*str;
	int		len;

	change_spec_long(spec);
	if ((len = nan_inf_0_long(num, spec)))
		return (len);
	else
	{
		s = get_s_long(num, spec);
		len = ft_strlen(s);
	}
	if (spec->widt >= len)
	{
		str = get_str_widt_long(spec, s, len);
		str = get_str_sign_long(spec, str, s, num);
		ft_putstr(str);
		free(str);
		free(s);
		return (len);
	}
	ft_putstr(s);
	free(s);
	return (len);
}
