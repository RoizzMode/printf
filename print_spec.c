/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:25:23 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/11 17:36:33 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_numb(t_spec *spec, int num)
{
	char *s;
	//char *str;
	int len;
	s = ft_itoa(num);
	if (spec->widt > (int)ft_strlen(s))
		len = spec->widt;
	else
		len = ft_strlen(s);
	if (spec->prec > len)
		len = spec->prec;

	ft_putnbr(num);
	return (len);
}

int	print_char(t_spec *spec, char c)
{
	char *s;
	int i;
	int len;

	i = 0;
	if (spec->widt)
	{
		s = ft_strnew(spec->widt);
		while (i < spec->widt)
			s[i++] = ' ';
		if (!(spec->minu))
			s[spec->widt - 1] = c;
		else
			s[0] = c;
		ft_putstr(s);
		len = ft_strlen(s);
		free(s);
		return (len);
	}
	else
		ft_putchar(c);
	return (1);
}

int	print_string(t_spec *spec, char *s)
{
	char *str;
	int i;
	int k;
	int len;

	i = 0;
	if ((int)ft_strlen(s) > spec->prec && spec->prec >= 0)
		len = spec->prec;
	else
		len = (int)ft_strlen(s);
	//ft_putnbr(len);
	//ft_putchar('\n');
	if (spec->widt > len)
	{
		str = ft_strnew(spec->widt);
		while (i < spec->widt)
			str[i++] = ' ';
		i = -1;
		if (spec->minu)
			while (s[++i] && i < len)
				str[i] = s[i];
		else
		{
			k = spec->widt - len - 1;
			while (s[++i] && str[++k])
				str[k] = s[i];
		}
		ft_putstr(str);
		free(str);
	}
	else
		while (i < len)
			write(1, &s[i++], 1);
	return (len);
}

int	print_point(t_spec *spec, char *p)
{
	(void)spec;
	ft_putnbr((int)p);
	return (1);
}
