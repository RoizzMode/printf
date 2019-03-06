/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_double4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:28:54 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:29:43 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_zero_widt_long(char *s, t_spec *spec, int len, long double num)
{
	int		k;
	int		i;
	char	*str;

	k = len - 1;
	len = spec->widt;
	str = ft_strnew(spec->widt);
	i = 0;
	while (i < spec->widt)
		if (spec->zero)
			str[i++] = '0';
		else
			str[i++] = ' ';
	i = get_i_zero_long(i, spec, k);
	while (k >= 0)
	{
		str[i] = s[k--];
		i--;
	}
	str = get_zero_sign_long(str, num, spec, s);
	ft_putstr(str);
	free(str);
	return (len);
}

int		print_zero_long(long double num, t_spec *spec)
{
	char	*s;
	int		len;

	len = get_len_zero_long(spec, num);
	s = get_zero_s_long(spec, num, len);
	if (spec->widt >= len)
		return (print_zero_widt_long(s, spec, len, num));
	ft_putstr(s);
	free(s);
	return (len);
}

int		print_inf_widt_long(char *s, t_spec *spec, int len)
{
	int		i;
	int		k;
	char	*str;

	k = len - 1;
	len = spec->widt;
	str = ft_strnew(spec->widt);
	i = 0;
	while (i < spec->widt)
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
	ft_putstr(str);
	free(str);
	free(s);
	return (len);
}

int		print_inf_long(t_spec *spec, long double num)
{
	char	*s;
	int		len;

	len = 3;
	if (spec->plu || spec->spac || read_sign_long(num) == 1)
		len++;
	s = ft_strnew(len);
	s[len - 1] = 'f';
	s[len - 2] = 'n';
	s[len - 3] = 'i';
	if (spec->plu || spec->spac || read_sign(num) == 1)
		s[0] = '-';
	if (spec->plu && read_sign(num) == 0)
		s[0] = '+';
	if (spec->spac && read_sign(num) == 1)
		s[0] = ' ';
	if (spec->widt >= len)
		return (print_inf_widt_long(s, spec, len));
	ft_putstr(s);
	free(s);
	return (len);
}

int		nan_inf_0_long(long double num, t_spec *spec)
{
	char	*s;
	int		len;

	len = 0;
	s = NULL;
	if (!read_base_long(num, 6) && !read_mantiss_long(num, 6, 0, 0))
		return (print_zero_long(num, spec));
	if (read_base_long(num, 6) == 1 && !read_mantiss_long(num, 6, 0, 0))
		return (print_inf_long(spec, num));
	if (read_base_long(num, 6) == 1 && read_mantiss_long(num, 6, 0, 0) == -1)
		return (print_nan_long(num, spec));
	return (0);
}
