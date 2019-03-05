/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_un_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 20:04:59 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/05 20:10:49 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*take_num(unsigned long long int num, t_spec *spec)
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

char	*get_str_un_numb(char *str, t_spec *spec)
{
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
	return (str);
}

int		get_i_un_numb(int i, int k, int minu)
{
	if (minu)
		i = k;
	else
		i--;
	return (i);
}

int		help_un_numb(t_spec *spec, char *s, int len)
{
	char	*str;
	int		k;
	int		i;

	i = 0;
	k = len - 1;
	len = spec->widt;
	str = ft_strnew(len);
	while (i < len)
		if (spec->zero && spec->prec < 0)
			str[i++] = '0';
		else
			str[i++] = ' ';
	i = get_i_un_numb(i, k, spec->minu);
	while (k >= 0)
	{
		str[i] = s[k--];
		i--;
	}
	str = get_str_un_numb(str, spec);
	ft_putstr(str);
	free(str);
	free(s);
	return (len);
}

int		print_un_numb(t_spec *spec, unsigned long long int num)
{
	char	*s;
	int		len;

	s = take_num(num, spec);
	len = (int)ft_strlen(s);
	if (spec->widt >= (int)ft_strlen(s))
		return (help_un_numb(spec, s, len));
	ft_putstr(s);
	free(s);
	return (len);
}
