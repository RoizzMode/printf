/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:33:17 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/04 19:41:33 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*help_point(t_spec *spec, char *s, int len)
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
	return (str);
}

int		print_point(t_spec *spec, void *p)
{
	char	*s;
	char	*str;
	int		len;

	s = print_pointer((unsigned long long int)p, spec);
	len = (int)ft_strlen(s);
	if (spec->widt > (int)ft_strlen(s))
	{
		str = help_point(spec, s, len);
		ft_putstr(str);
		free(s);
		free(str);
		return (len);
	}
	ft_putstr(s);
	free(s);
	return (len);
}

int		print_proc(t_spec *spec, char c)
{
	char	*s;
	int		i;
	int		len;

	if (spec->widt > 1)
	{
		i = 0;
		len = spec->widt;
		s = ft_strnew(len);
		while (i < len)
			if (spec->zero && !spec->minu)
				s[i++] = '0';
			else
				s[i++] = ' ';
		if (spec->minu)
			s[0] = '%';
		else
			s[len - 1] = '%';
		ft_putstr(s);
		free(s);
		return (len);
	}
	ft_putchar(c);
	return (1);
}
