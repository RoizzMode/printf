/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:25:23 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/14 18:07:16 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_signed_numb(t_spec *spec, long long int num)
{
	char *s;
	//char *str;
	int len;
	if (spec->type == 'i' || spec->type == 'd')
		s = ft_itoa(num);
	//else if (spec->type == 'o')
	//	s = dec_to_oct(num, spec->octo);
	//else if (spec->type == 'u')
	//	s = ft_itoa(num);
	//else if (spec->type == 'x')
	//	s = dec_to_hex(num, spec->octo);
	//else if (spec->type == 'X')
	//	s = dec_to_heX(num, spec->octo);
	if (spec->widt > (int)ft_strlen(s))
		len = spec->widt;
	else
		len = ft_strlen(s);
	if (spec->prec > len)
		len = spec->prec;
	ft_putstr(s);
	return (len);
}

int	print_unsigned_numb(t_spec *spec, unsigned long long int num)
{
	char *s;
	char *str;
	int len;
	int i = 0;
	int k;

	if (spec->type == 'o')
		s = dec_to_oct(num, spec);
	else if (spec->type == 'u')
		s = ft_itoa(num);
	else if (spec->type == 'x')
		s = dec_to_hex(num, spec);
	else
		s = dec_to_heX(num, spec);
	len = (int)ft_strlen(s);
	//printf("%d\n", len);
	if (spec->widt > (int)ft_strlen(s))
	{
		k = len - 1;
		len = spec->widt;
		str = ft_strnew(len);
		while (i < len)
		{
			if (spec->zero && spec->prec < 0)
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
			str[i] = s[k];
			i--;
			k--;
		}
		ft_putstr(str);
		free(s);
		free(str);
		return(len);
	}
	ft_putstr(s);
	free(s);
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
	int flag;

	i = 0;
	flag = 0;
	if ((void *)s == NULL)
	{
		s = ft_strnew(6);
		s[0] = '(';
		s[1] = 'n';
		s[2] = 'u';
		s[3] = 'l';
		s[4] = 'l';
		s[5] = ')';
		flag = 1;
	}
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
		if (flag)
			free (s);
	}
	else
		while (i < len)
			write(1, &s[i++], 1);
	return((len > spec->widt) ? (len) : (spec->widt));
}

int	print_point(t_spec *spec, char *p)
{
	(void)spec;
	ft_putnbr((int)p);
	return (1);
}
