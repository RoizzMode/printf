/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:44:45 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/04 20:03:58 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		help_char(char c, int len)
{
	ft_putchar(c);
	return (len + 1);
}

int		print_char(t_spec *spec, char c)
{
	char	*s;
	int		i;
	int		len;

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
		if (!c)
			len = help_char(c, len);
		free(s);
		return (len);
	}
	else
		ft_putchar(c);
	return (1);
}

void	help_string(t_spec *spec, char *s, int len)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
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
		ft_putstr(s);
}

int		print_string(t_spec *spec, char *s)
{
	int i;
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
	help_string(spec, s, len);
	if (flag)
		free(s);
	return ((len > spec->widt) ? (len) : (spec->widt));
}
