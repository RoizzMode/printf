/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:34:52 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:35:57 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int64_t		ft_pow2(int n, int64_t p)
{
	int64_t		i;
	int64_t		a;
	int64_t		check;

	i = 1;
	a = n;
	check = a;
	if (n == 0)
		return (0);
	if (p == 0)
		return (1);
	while (i < p)
	{
		check = a;
		a = a * n;
		if (check < a && n < 0)
			return (0);
		if (check > a && n > 0)
			return (-1);
		i++;
	}
	return (a);
}

int			ft_len(int64_t n)
{
	int i;

	i = 0;
	while (n > 9 || n < -9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int			len_after(int prec)
{
	int len_after;

	if (prec > 0)
		len_after = prec + 1;
	else
		len_after = 0;
	return (len_after);
}

char		*help_itoa2(int64_t n, t_spec *spec, char *s, int len)
{
	if (n < 0 && !((spec->minu || spec->zero)
				&& spec->widt >= (len + len_after(spec->prec))))
		s[0] = '-';
	if (n > 0 && spec->plu && !((spec->minu || spec->zero)
				&& spec->widt >= (len + len_after(spec->prec))))
		s[0] = '+';
	if (n > 0 && spec->spac && !((spec->minu || spec->zero)
				&& spec->widt >= (len + len_after(spec->prec))))
		s[0] = ' ';
	return (s);
}

int			check_0(int64_t n)
{
	if (n < 0)
		return (-1);
	return (0);
}
