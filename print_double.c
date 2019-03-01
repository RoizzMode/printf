/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:18:05 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/01 16:09:53 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <math.h>

int read_base(double num)
{
	unsigned char *casted;
	int i;
//	int j;
	int one;
	int null;

	casted = (unsigned char *) & num;
	one = 0;
	null = 0;
/*	i = 7;
	while (i > -1)
	{
		j = 7;
		while (j > -1)
		{
			printf(" %d %d:",i,j);
			if (casted[i] & (1 << j))
			{
				printf("1");
				one = 1;
			}
			else
			{
				printf("0");
				null = 1;
			}
			j--;
		}
		i--;
	}
	printf("\n");*/
	i = 6;
	while (i > -1)
	{
		if (casted[7] & (1 << i))
		{
		//	printf("1");
			one = 1;
		}
		else
		{
		//	printf("0");
			null = 1;
		}
		i--;
	}
	i = 7;
	while (i > 3)
	{
		if (casted[6] & (1 << i))
		{
		//	printf("1");
			one = 1;
		}
		else
		{
		//	printf("0");
			null = 1;
		}
		i--;
	}
	if (one && !null)
		return (1);
	if (!one && null)
		return (0);
	return (-1);
}

int read_mantiss(double num)
{
	unsigned char *casted;
	int i;
	int j;
	int one;
	int null;

	casted = (unsigned char *) & num;
	one = 0;
	null = 0;
	i = 3;
	while (i > -1)
	{
		if (casted[6] & (1 << i))
		{
//			printf("1");
			one = 1;
		}
		else
		{
//			printf("0");
			null = 1;
		}
		i--;
	}
	i = 5;
	while (i > 1)
	{
		j = 7;
		while (j > -1)
		{
			if (casted[1] & (1 << j))
			{
//				printf("1");
				one = 1;
			}
			else
			{
//				printf("0");
				null = 1;
			}
			j--;
		}
		i--;
	}
	if (one && !null)
		return (1);
	if (!one && null)
		return (0);
	return (-1);
}

int	nan_inf_0(double num, t_spec *spec)
{
	char *s;
	char *str;
	int i;
	int k;
	int len;
//	printf("%d", read_base(num));
	if (read_base(num) == 1 && read_mantiss(num) == -1)
	{
		s = ft_strnew(3);
		s[0] = 'n';
		s[1] = 'a';
		s[2] = 'n';
		len = 3;
		if (spec->widt > len)
		{
			k = len - 1;
			len = spec->widt;
			str = ft_strnew(spec->widt);
			i = 0;
			while (i < spec->widt)
			{
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
			free(str);
			free(s);
			return (len);
		}
		ft_putstr(s);
		free(s);
		return (len);
	}
	return (0);
}

int print_double(t_spec *spec, double num)
{
	t_float *tf;
	char *s;
	char *str;
	int len;
	int i;
	int k;

	tf = (t_float*)malloc(sizeof(t_float));
	tf->before_p = (int64_t)num;
	tf->after_p = num - tf->before_p;
	if (spec->plu && spec->spac)
		spec->spac = 0;
	len = 0;
	if ((len = nan_inf_0(num, spec)))
		return (len);
	else
	{
		s = ft_itoa2(tf->before_p, spec);
		round_p(tf, spec->prec);
		if (spec->prec != 0)
			s = ft_strjoin(s, itoa_after_p(tf->after_p));
		len = ft_strlen(s);
	}
	//ft_putstr(s);
	if (spec->widt > len)
	{
		if (spec->zero && spec->minu)
			spec->zero = 0;
		k = len - 1;
		len = spec->widt;
		str = ft_strnew(spec->widt);
		i = 0;
		while (i < spec->widt)
		{
			if (spec->zero)
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
		if (num < 0 && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = '-';
			else
				str[spec->widt - ft_strlen(s) + 1] = '-';
		}
		if (num > 0 && spec->plu && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = '+';
			else
				str[spec->widt - ft_strlen(s) + 1] = '+';
		}
		if (num > 0 && spec->spac && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = ' ';
			else
				str[spec->widt - ft_strlen(s) + 1] = ' ';
		}
		ft_putstr(str);
		free(str);
		free(s);
		return (len);
	}
	ft_putstr(s);
	return(len);
}

int print_long_double(t_spec *spec, long double num)
{
	(void)spec;
	num = 0;
	return(0);
}
