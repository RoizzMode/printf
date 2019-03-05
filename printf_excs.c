/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_excs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:00 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/05 19:54:52 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		read_base(double num)
{
	unsigned char	*casted;
	int				i;
	int				one;
	int				null;

	casted = (unsigned char *)&num;
	one = 0;
	null = 0;
	i = 6;
	while (i > -1)
		if (casted[7] & (1 << i--))
			one = 1;
		else
			null = 1;
	i = 7;
	while (i > 3)
		if (casted[6] & (1 << i--))
			one = 1;
		else
			null = 1;
	if ((one && !null) || (!one && null))
		return ((one && !null) ? (1) : (0));
	return (-1);
}

int		help_mantiss(int null, int one)
{
	if (one && !null)
		return (1);
	if (!one && null)
		return (0);
	return (-1);
}

int		read_mantiss(double num, int i)
{
	unsigned char	*casted;
	int				j;
	int				one;
	int				null;

	casted = (unsigned char *)&num;
	one = 0;
	null = 0;
	i = 3;
	while (i > -1)
		if (casted[6] & (1 << i--))
			one = 1;
		else
			null = 1;
	i = 5;
	while (i-- > 1)
	{
		j = 7;
		while (j > -1)
			if (casted[i] & (1 << j--))
				one = 1;
			else
				null = 1;
	}
	return (help_mantiss(null, one));
}

int		read_sign(double num)
{
	unsigned char *casted;

	casted = (unsigned char*)&num;
	if (casted[7] & (1 << 7))
		return (1);
	return (0);
}

int		help_inf(char *s, t_spec *spec, int len)
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
		str[i] = s[k--];
		i--;
	}
	ft_putstr(str);
	free(s);
	free(str);
	return (len);
}

int		print_inf(t_spec *spec, double num)
{
	char	*s;
	int		len;

	len = 3;
	if (spec->plu || spec->spac || read_sign(num) == 1)
		len++;
	s = ft_strnew(len);
	s[len - 1] = 'f';
	s[len - 2] = 'n';
	s[len - 3] = 'i';
	if (spec->plu || spec->spac || read_sign(num) == 1)
		s[0] = '-';
	if (spec->plu && read_sign(num) == 0)
		s[0] = '+';
	if (spec->spac && read_sign(num) == 0)
		s[0] = ' ';
	if (spec->widt >= len)
		return (help_inf(s, spec, len));
	return (len);
}

int		help_nan(t_spec *spec, char *s, int len)
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
		str[i] = s[k--];
		i--;
	}
	ft_putstr(str);
	free(str);
	free(s);
	return (len);
}

int		print_nan(t_spec *spec)
{
	char	*s;
	int		len;

	s = ft_strnew(3);
	s[0] = 'n';
	s[1] = 'a';
	s[2] = 'n';
	len = 3;
	if (spec->widt > len && len > 0)
		return (help_nan(spec, s, len));
	ft_putstr(s);
	free(s);
	return (len);
}

int		nan_inf_0(double num, t_spec *spec)
{
	if (!read_base(num) && !read_mantiss(num, 3))
		return (print_zero(num, spec));
	if (read_base(num) == 1 && !read_mantiss(num, 3))
		return (print_inf(spec, num));
	if (read_base(num) == 1 && read_mantiss(num, 3) == -1)
		return (print_nan(spec));
	return (0);
}
