/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_double2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:24:16 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:25:35 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		read_base_long(long double num, int i)
{
	unsigned char	*casted;
	int				one;
	int				null;

	casted = (unsigned char *)&num;
	one = 0;
	null = 0;
	while (i > -1)
		if (casted[9] & (1 << i--))
			one = 1;
		else
			null = 1;
	i = 7;
	while (i > -1)
		if (casted[8] & (1 << i--))
			one = 1;
		else
			null = 1;
	if (casted[7] & (1 << 7))
		one = 1;
	else
		null = 1;
	if ((one && !null) || (!one && null))
		return ((one && !null) ? (1) : (0));
	return (-1);
}

int		read_mantiss_long(long double num, int i, int one, int null)
{
	unsigned char	*casted;
	int				j;

	casted = (unsigned char *)&num;
	while (i > -1)
		if (casted[7] & (1 << i--))
			one = 1;
		else
			null = 1;
	i = 6;
	while (i > 1)
	{
		j = 7;
		while (j > -1)
			if (casted[i] & (1 << j--))
				one = 1;
			else
				null = 1;
		i--;
	}
	if ((one && !null) || (!one && null))
		return ((one && !null) ? (1) : (0));
	return (-1);
}

int		read_sign_long(long double num)
{
	unsigned char *casted;

	casted = (unsigned char *)&num;
	if (casted[9] & (1 << 7))
		return (1);
	return (0);
}

int		get_nan_long(t_spec *spec, int len, char *s)
{
	int		k;
	int		i;
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
		str[i] = s[k--];
		i--;
	}
	ft_putstr(str);
	free(str);
	free(s);
	return (len);
}

int		print_nan_long(long double num, t_spec *spec)
{
	int		len;
	char	*s;

	s = ft_strnew(3);
	s[0] = 'n';
	s[1] = 'a';
	s[2] = 'n';
	len = 3;
	if (spec->widt > len && len > 0)
		return (get_nan_long(spec, len, s));
	ft_putstr(s);
	free(s);
	return (len);
}
