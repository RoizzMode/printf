/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:32:35 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/03 14:07:57 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *itoa_after_p(double num)
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

double round_p(double num, int prec)
{
	double ld;
	ld = ((int64_t)(num * ft_pow2(10, prec) +
				(num >= 0 ? 0.5 : -0.5))) / (double)ft_pow2(10, prec);
	num = ld;
	return (num);
}
int print_float(t_spec *spec, long double num)
{
	unsigned char *casted;

	if (spec->prec < 0)
		spec->prec = 6;
	printf("%Lf", num);
	if (spec->size == 'L')
		print_long_double(spec, num);
	else
		print_double(spec, (double)num);
	casted = (unsigned char *) & num;
	return (1);
}

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

static int	ft_len(int64_t n)
{
	int i;

	i = 0;
	while (n > 9 || n < -9)
	{
		i++;
		n /= 10;
	}
//	if (n < 0)
//		i++;
	return (i);
}

char		*ft_itoa2(int64_t n, t_spec* spec)
{
	int		i;
	char	*s;
	int64_t		notn;
	int		check;
	int len;
	int len_after;

	check = 1;
	notn = n;
	len = ft_len(n);
	if (spec->prec > 0)
		len_after = spec->prec + 1;
	else
		len_after = 0;
	if (n < 0)
		check = -1;
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
	if (check < 0 && !((spec->minu || spec->zero) && spec->widt >= (len + len_after)))
		s[0] = '-';
	if (check > 0 && spec->plu && !((spec->minu || spec->zero) && spec->widt >= (len + len_after)))
		s[0] = '+';
	if (check > 0 && spec->spac && !((spec->minu || spec->zero) && spec->widt >= (len + len_after)))
		s[0] = ' ';
	return (s);
}
