/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:55:57 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/03 19:34:26 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_bits(long double num)
{
	unsigned char *casted;
	casted = (unsigned char *) & num;
	int i;
	int j;
	i = 9;
	while (i > -1)
	{
		j = 7;
		while (j > -1)
		{
			printf(" |%d %d: ",i, j);
			if (casted[i] & (1 << j))
				printf("1|");
			else
				printf("0|");
			j--;
		}
		i--;
	}
}

int read_base_long(long double num)
{
	unsigned char *casted;
	int i;
	int one;
	int null;

	casted = (unsigned char *) & num;
	one = 0;
	null = 0;
	i = 6;
	while (i > -1)
	{
		if (casted[9] & (1 << i))
			one = 1;
		else
			null = 1;
		i--;
	}
	i = 7;
	while (i > -1)
	{
		if (casted[8] & (1 << i))
			one = 1;
		else
			null = 1;
		i--;
	}
	if (casted[7] & (1 << 7))
		one = 1;
	else
		null = 1;
	if (one && !null)
		return (1);
	if (!one && null)
		return (0);
	return (-1);
}

int read_mantiss_long(long double num)
{
	unsigned char *casted;
	int i;
	int j;
	int one;
	int null;

	casted = (unsigned char *) & num;
	one = 0;
	null = 0;
	i = 6;
	while (i > -1)
	{
		if (casted[7] & (1 << i))
			one = 1;
		else
			null = 1;
		i--;
	}
	i = 6;
	while (i > 1)
	{
		j = 7;
		while (j > -1)
		{
			if (casted[1] & (1 << j))
				one = 1;
			else
				null = 1;
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

int read_sign_long(long double num)
{
	unsigned char *casted;

	casted = (unsigned char *) & num;
	if (casted[9] & (1 << 7))
		return(1);
	return (0);
}

int print_zero_long(long double num, t_spec *spec)
{
	char *s;
	int len;
	int i;
	int k;
	char *str;
	int len_after;

	len = 1;
	if (spec->spac || spec->plu || read_sign(num) == 1)
		len++;
	if (spec->prec > -1)
		len += spec->prec + 1;
	if (spec->prec > 0)
		len_after = spec->prec + 1;
	else
		len_after = 0;
	s = ft_strnew(len);
	i = 0;
	while (i < len)
		s[i++] = '0';
	if (spec->spac || spec->plu || read_sign(num) == 1)
		s[2] = '.';
	else
		s[1] = '.';
	if (read_sign(num) == 1 && !((spec->minu || spec->zero) && spec->widt >= (len + len_after)))
		s[0] = '-';
	if (read_sign(num) == 0 && spec->plu && !((spec->minu || spec->zero) && spec->widt >= (len + len_after)))
		s[0] = '+';
	if (read_sign(num) == 0 && spec->spac && !((spec->minu || spec->zero) && spec->widt >= (len + len_after)))
		s[0] = ' ';
	if (spec->widt >= len)
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
		if (read_sign(num) == 1 && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = '-';
			else
				str[spec->widt - ft_strlen(s) + 1] = '-';
		}
		if (read_sign(num) == 0 && spec->plu && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = '+';
			else
				str[spec->widt - ft_strlen(s) + 1] = '+';
		}
		if (read_sign(num) == 0 && spec->spac && (spec->minu || spec->zero))
		{
			if (spec->minu || spec->zero)
				str[0] = ' ';
			else
				str[spec->widt - ft_strlen(s) + 1] = ' ';
		}
		ft_putstr(str);
		free(str);
		return(len);
	}
	ft_putstr(s);
	free(s);
	return (len);
}

int		print_inf_long(t_spec *spec, long double num)
{
	char *s;
	int len;
	int i;
	int k;
	char *str;

	len = 3;
	if (spec->plu || spec->spac)
		len++;
	s = ft_strnew(len);
	i = 0;
	s[len - 1 - i++] = 'f';
	s[len - 1 - i++] = 'n';
	s[len - 1 - i++] = 'i';
	if ((spec->plu || spec->spac) && read_sign(num) == 1)
		s[0] = '-';
	if (spec->plu && read_sign(num) == 0)
		s[0] = '+';
	if (spec->spac && read_sign(num) == 1)
		s[0] = ' ';
	if (spec->widt >= len)
	{
		k = len - 1;
		len = spec->widt;
		str = ft_strnew(spec->widt);
		i = 0;
		while (i < spec->widt)
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
		ft_putstr(str);
		free(str);
		return(len);
	}
	return (len);
}

int	nan_inf_0_long(long double num, t_spec *spec)
{
	char *s;
	char *str;
	int i;
	int k;
	int len;

	len = 0;
	s = NULL;
//	read_bits(num);
	if (!read_base_long(num) && !read_mantiss_long(num))
		return(print_zero(num, spec));
	if (read_base_long(num) == 1 && !read_mantiss_long(num))
		return(print_inf(spec, num));
	if (read_base_long(num) == 1 && read_mantiss_long(num) == -1)
	{
		s = ft_strnew(3);
		s[0] = 'n';
		s[1] = 'a';
		s[2] = 'n';
		len = 3;
	}
	if (spec->widt > len && len > 0)
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
	if (s)
	{
		ft_putstr(s);
		free(s);
		return (len);
	}
	return (0);
}

int print_long_double(t_spec *spec, long double num)
{

	t_dfloat *tf;
	char *s;
	char *str;
	char *temp;
	int len;
	int i;
	int k;

	if (spec->prec == -1)
		spec->prec = 6;
	if (spec->plu && spec->spac)
		spec->spac = 0;
	len = 0;
	if ((len = nan_inf_0_long(num, spec)))
		return (len);
	else
	{
		num = round_p_long(num, spec->prec);
		tf = (t_dfloat*)malloc(sizeof(t_dfloat));
		tf->before_p = (int64_t)num;
		tf->after_p = num - tf->before_p;
		s = ft_itoa2(tf->before_p, spec);
		if (spec->prec != 0)
		{
			str = ft_strdup(s);
			tf->after_p = (int64_t)(tf->after_p * (ft_pow2(10, spec->prec)));
			temp = itoa_after_p_long(tf->after_p);
			free(s);
			s = ft_strjoin(str, temp);
			free(str);
			free(temp);
		}
		len = ft_strlen(s);
	}
	if (spec->widt >= len)
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
		free(tf);
		return (len);
	}
	free(tf);
	ft_putstr(s);
	free(s);
	return(len);
}
