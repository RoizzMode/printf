/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_zero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:19:21 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:32:10 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_str_zero(char *str, char *s, t_spec *spec, double num)
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

void	print_free(char *s, char *str)
{
	ft_putstr(str);
	free(str);
	free(s);
}

int		help_print0(double num, t_spec *spec, char *s, int len)
{
	char	*str;
	int		i;
	int		k;

	if (spec->zero && spec->minu)
		spec->zero = 0;
	k = len - 1;
	len = spec->widt;
	str = ft_strnew(spec->widt);
	i = 0;
	while (i < spec->widt)
		if (spec->zero)
			str[i++] = '0';
		else
			str[i++] = ' ';
	i = get_i(i, k, spec->minu);
	while (k >= 0)
	{
		str[i] = s[k--];
		i--;
	}
	str = get_str_zero(str, s, spec, num);
	print_free(s, str);
	return (len);
}

char	*get_str_zero2(char *s, t_spec *spec, double num, int len)
{
	int len_after;

	if (spec->prec > 0)
		len_after = spec->prec + 1;
	else
		len_after = 0;
	if (spec->spac || spec->plu || read_sign(num) == 1)
		s[2] = '.';
	else
		s[1] = '.';
	if (read_sign(num) == 1 && !((spec->minu || spec->zero)
				&& spec->widt >= (len + len_after)))
		s[0] = '-';
	if (read_sign(num) == 0 && spec->plu && !((spec->minu || spec->zero)
				&& spec->widt >= (len + len_after)))
		s[0] = '+';
	if (read_sign(num) == 0 && spec->spac && !((spec->minu || spec->zero)
				&& spec->widt >= (len + len_after)))
		s[0] = ' ';
	return (s);
}

int		print_zero(double num, t_spec *spec)
{
	char	*s;
	int		len;
	int		i;

	len = 1;
	if (spec->spac || spec->plu || read_sign(num) == 1)
		len++;
	if (spec->prec > -1)
		len += spec->prec + 1;
	s = ft_strnew(len);
	i = 0;
	while (i < len)
		s[i++] = '0';
	s = get_str_zero2(s, spec, num, len);
	if (spec->widt >= len)
		return (help_print0(num, spec, s, len));
	ft_putstr(s);
	free(s);
	return (len);
}
