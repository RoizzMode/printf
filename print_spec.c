/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:25:23 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:33:39 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_str_signed(t_spec *spec, char *str, long long num, int len)
{
	if (!check_negative(num, spec) && (spec->minu || spec->zero))
		str = get_str_char(spec, str, len, '-');
	if (check_negative(num, spec) && spec->plu &&
			(spec->minu || spec->zero))
		str = get_str_char(spec, str, len, '+');
	if (check_negative(num, spec) && spec->spac &&
			(spec->minu || spec->zero))
		str = get_str_char(spec, str, len, ' ');
	return (str);
}

int			get_i_signed(int i, int k, int minu)
{
	if (minu)
		i = k;
	else
		i--;
	return (i);
}

int			help_signed(t_spec *spec, char *s, int len, long long num)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = len - 1;
	len = spec->widt;
	str = ft_strnew(len);
	while (i < len)
		if (spec->zero && spec->prec < 0)
			str[i++] = '0';
		else
			str[i++] = ' ';
	i = get_i_signed(i, k, spec->minu);
	while (k >= 0)
	{
		str[i] = s[k--];
		i--;
	}
	str = get_str_signed(spec, str, num, len);
	ft_putstr(str);
	free(s);
	free(str);
	return (len);
}

int			print_signed_numb(t_spec *spec, long long int num)
{
	char	*s;
	int		len;

	s = signed_itoa(num, spec);
	len = (int)ft_strlen(s);
	if (spec->widt >= (int)ft_strlen(s))
		return (help_signed(spec, s, len, num));
	ft_putstr(s);
	free(s);
	return (len);
}
