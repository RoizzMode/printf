/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:06:31 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/04 14:41:17 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


char *itoa_after_p_long(long double num, int prec)
{
	char *s;
	int i;
	int64_t unnum;
	int k;
	int zeros;

	zeros = 0;
//	num = (int64_t)(num * (ft_pow2(10, prec)));
	i = 0;
	while (i < prec)
	{
		num = num * 10;
		if ((num > 0 && num < 1) || (num < 0 && num > -1))
			zeros++;
		i++;
	}
	unnum = (int64_t)num;
//	printf("\n%.20Lf\n", num);
//	printf("%lld\n", unnum);
	if (unnum < 0)
		unnum *= -1;
	i = num_len(unnum) + zeros;
	if (i >= prec)
	{
		s = (char*)malloc(sizeof(char) * i + 2);
		if (!s)
			return (NULL);
		s[i + 1] = '\0';
		k = 0;
		while (k < i + 1)
		{
			s[k++] = '0';
		}
	}
	else
	{
		k = 0;
		s = (char*)malloc(sizeof(char) * prec + 1);
		if (!s)
			return (NULL);
		s[prec] = '\0';
		while (k < prec + 1)
		{
			s[k++] = '0';
		}
//		ft_putstr(s);
	}
//	s = (char*)malloc(sizeof(char) * i + 2);
//	if (!s)
//		return (NULL);
//	s[i + 1] = '\0';
	s[i--] = (unnum % 10) + '0';
	while (unnum /= 10)
		s[i--] = (unnum % 10 + '0');
	s[0] = '.';
	//ft_putstr(s);
	return (s);
}

long double round_p_long(long double num, int prec)
{
	long double ld;
//	printf("%Lf", num);
	ld = ((int64_t)(num * ft_pow2(10, prec) +
				(num >= 0 ? 0.5 : -0.5))) / (long double)ft_pow2(10, prec);
	num = ld;
//	printf("%Lf", ld);
	return (num);
}
