/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_excs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:00 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:23:13 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
