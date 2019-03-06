/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:32:35 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:35:26 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*help_itoa_after(int prec, int i)
{
	int		k;
	char	*s;

	if (i >= prec)
	{
		s = (char*)malloc(sizeof(char) * i + 2);
		if (!s)
			return (NULL);
		s[i + 1] = '\0';
		k = 0;
		while (k < i + 1)
			s[k++] = '0';
	}
	else
	{
		k = 0;
		s = (char*)malloc(sizeof(char) * prec + 1);
		if (!s)
			return (NULL);
		s[prec] = '\0';
		while (k < prec + 1)
			s[k++] = '0';
	}
	return (s);
}

char		*itoa_after_p(double num, int prec)
{
	char	*s;
	int		i;
	int64_t	unnum;
	int		zeros;

	zeros = 0;
	i = 0;
	while (i < prec)
	{
		num = num * 10;
		if ((num > 0 && num < 1) || (num < 0 && num > -1))
			zeros++;
		i++;
	}
	unnum = (int64_t)num;
	if (unnum < 0)
		unnum *= -1;
	i = num_len(unnum) + zeros;
	s = help_itoa_after(prec, i);
	s[i--] = (unnum % 10) + '0';
	while (unnum /= 10)
		s[i--] = (unnum % 10 + '0');
	s[0] = '.';
	return (s);
}

double		round_p(double num, int prec)
{
	double	ld;

	ld = ((int64_t)(num * ft_pow2(10, prec) +
				(num >= 0 ? 0.5 : -0.5))) / (double)ft_pow2(10, prec);
	num = ld;
	return (num);
}

char		*ft_itoa2(int64_t n, t_spec *spec)
{
	int			i;
	char		*s;
	int64_t		notn;
	int			check;
	int			len;

	notn = n;
	len = ft_len(n);
	check = check_0(n);
	if (n < 0 || spec->plu || spec->spac)
		len++;
	s = (char*)malloc(sizeof(char) * len + 2);
	if (!s)
		return (NULL);
	s[len + 1] = '\0';
	i = 0;
	while (i < len)
		s[i++] = '0';
	i = len;
	s[i--] = (notn % 10) * check + '0';
	while (notn /= 10)
		s[i--] = (check * notn % 10 + '0');
	s = help_itoa2(n, spec, s, len);
	return (s);
}
