/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:06:31 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/03 16:16:39 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


char *itoa_after_p_long(long double num)
{
	char *s;
	int i;
	int64_t unnum;

	unnum = (int64_t)num;
	if (unnum < 0)
		unnum *= -1;
	i = num_len(unnum);
	s = (char*)malloc(sizeof(char) * i + 2);
	if (!s)
		return (NULL);
	s[i + 1] = '\0';
	s[i--] = (unnum % 10) + '0';
	while (unnum /= 10)
		s[i--] = (unnum % 10 + '0');
	s[0] = '.';
	return (s);
}

long double round_p_long(long double num, int prec)
{
	long double ld;
	ld = ((int64_t)(num * ft_pow2(10, prec) +
				(num >= 0 ? 0.5 : -0.5))) / (long double)ft_pow2(10, prec);
	num = ld;
	return (num);
}
