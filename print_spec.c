/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:25:23 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/17 15:08:42 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int check_negative(long long int num, t_spec *spec)
{
	long long int unnum;
	if (spec->size == 'l')
		unnum = (long int)num;
	else if (spec->size == 's')
		unnum = (char)num;
	else if (spec->size == 'h')
		unnum = (short int)num;
	else if (spec->size == 'b')
		unnum = num;
	else
		unnum = (int)num;
	if (unnum < 0)
		return (0);
	return (1);
}

char *signed_itoa(long long int num, t_spec *spec)
{
	char  *oct;
	int len;
	int check;
	long long int unnum;
	int i = 0;

	len = 0;
	if (!spec->prec && !num && !spec->octo)
	{
		//printf("here");
		return("");
	}
	if (spec->plu && spec->spac)
		spec->spac = 0;
	if (spec->minu && spec->zero)
		spec->zero = 0;
	if (spec->size == 'l')
		unnum = (long int)num;
	else if (spec->size == 's')
		unnum = (char)num;
	else if (spec->size == 'h')
		unnum = (short int)num;
	else if (spec->size == 'b')
		unnum = num;
	else
		unnum = (int)num;
	//printf("%lld", num);
	while (unnum / 10)
	{
	//ft_putnbr(len);
		len++;
		unnum /= 10;
	}
	//ft_putnbr(len);
	check = 1;
	if (spec->size == 'l')
		unnum = (long int)num;
	else if (spec->size == 's')
		unnum = (char)num;
	else if (spec->size == 'h')
		unnum = (short int)num;
	else if (spec->size == 'b')
		unnum = num;
	else
		unnum = (int)num;
	if (unnum < 0)
		check = -1;
//	ft_putnbr(len);
	if (len < spec->prec)
		len = spec->prec - 1;
	if ((unnum < 0 || spec->plu || spec->spac))
		len++;
//	printf("%lld", num);
//	ft_putnbr(len);
	oct = (char*)malloc(sizeof(char) * len + 2);
	if (!oct)
		return (NULL);
	while (i < len)
		oct[i++] = '0';
//	ft_putstr(oct);
//	printf("%d", len);
	oct[len + 1] = '\0';
	oct[len--] = (unnum % 10) * check + '0';
//	printf("%d", check);
	while (unnum /= 10)
		oct[len--] = (unnum % 10) * check + '0';
	if (check < 0 && (!(spec->minu || spec->zero) || (spec->zero && spec->widt < (int)ft_strlen(oct) && spec->prec < 0)))
		oct[0] = '-';
	if (check > 0 && spec->plu && (!(spec->minu || spec->zero) || (spec->zero && spec->widt < (int)ft_strlen(oct) && spec->prec < 0)))
		oct[0] = '+';
	if (check > 0 && spec->spac && (!(spec->minu || spec->zero) || (spec->zero && spec->widt < (int)ft_strlen(oct) && spec->prec < 0)))
		oct[0] = ' ';
	//printf("\n%s\n", oct);
	return (oct);
}

int	print_signed_numb(t_spec *spec, long long int num)
{
	char *s;
	char *str;
	int len;
	int i;
	int k;

	i = 0;
	//if (spec->type == 'i' || spec->type == 'd')
	//printf("%lld", num);
	s = signed_itoa(num, spec);
	//else if (spec->type == 'o')
	//	s = dec_to_oct(num, spec->octo);
	//else if (spec->type == 'u')
	//	s = ft_itoa(num);
	//else if (spec->type == 'x')
	//	s = dec_to_hex(num, spec->octo);
	//else if (spec->type == 'X')
	//	s = dec_to_heX(num, spec->octo);
	//if (spec->widt > (int)ft_strlen(s))
	//	len = spec->widt;
	//else
	//	len = ft_strlen(s);
	//if (spec->prec > len)
	//	len = spec->prec;
	//ft_putstr(s);
	len = (int)ft_strlen(s);
//	printf("%d", len);
	if (spec->widt >= (int)ft_strlen(s))
	{
		k = len - 1;
		len = spec->widt;
//		if ((num < 0 || spec->plu || spec->spac) && spec->minu)
//			k++;
		str = ft_strnew(len);
//		printf("here");
		while (i < len)
		{
			if (spec->zero && spec->prec < 0)
				str[i++] = '0';
			else
				str[i++] = ' ';
		}
//		printf("%d", check_negative(num, spec));

		//if (!check_negative(num, spec) && (spec->minu || spec->zero))
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
		if (!check_negative(num, spec) && (spec->minu || spec->zero))
		{
			//printf("here");
			if (spec->prec > 0 && spec->prec > (int)ft_strlen(s))
				str[len - spec->prec - 1] = '-';
			else if (spec->minu || spec->zero)
				str[0] = '-';
			else
				str[len - spec->widt + 1] = '-';
		}
		if (check_negative(num, spec) && spec->plu && (spec->minu || spec->zero))
		{
		//	printf("here");
			if (spec->prec > 0 && spec->prec > (int)ft_strlen(s))
				str[len - spec->prec - 1] = '+';
			else if (spec->minu || spec->zero)
				str[0] = '+';
			else
				str[len - spec->widt + 1] = '+';
		}
		if (check_negative(num, spec) && spec->spac && (spec->minu || spec->zero))
		{
		//	printf("here");
			if (spec->prec > 0 && spec->prec > (int)ft_strlen(s))
				str[len - spec->prec - 1] = ' ';
			else if (spec->minu || spec->zero)
				str[0] = ' ';
			else
				str[len - spec->widt + 1] = ' ';
		}

		ft_putstr(str);
		if (ft_strlen(s))
			free(s);
		free(str);
		return(len);
	}
	ft_putstr(s);
	if (ft_strlen(s))
		free(s);
	return (len);
}

int	print_unsigned_numb(t_spec *spec, unsigned long long int num)
{
	char *s;
	char *str;
	int len;
	int i = 0;
	int k;

	//if (spec->octo && (spec->type == 'X' || spec->type == 'x') && !num)
	//	return (0);
	//if (spec->octo && (spec->type == 'o') && !num && !spec->prec)
	//	return (0);
	if (spec->minu && spec->zero)
		spec->zero = 0;
	if (spec->type == 'o')
		s = dec_to_oct(num, spec);
	else if (spec->type == 'u')
		s = unsigned_itoa(num, spec);
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
		if (spec->type == 'X' && spec->octo && spec->zero)
			str[1] = 'X';
		if (spec->type == 'x' && spec->octo && spec->zero)
			str[1] = 'x';
		while (k >= 0)
		{
			str[i] = s[k];
			i--;
			k--;
		}
		ft_putstr(str);
		if (ft_strlen(s))
			free(s);
		free(str);
		return(len);
	}
	//if (spec->type == 'X' && spec->octo && spec->zero)
	//	s[1] = 'X';
	ft_putstr(s);
	if (ft_strlen(s))
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
		if (!c)
		{
			ft_putchar(c);
			len++;
		}
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

int	print_point(t_spec *spec, void *p)
{
	char *s;
	char *str;
	int len;
	int i = 0;
	int k;

	//if (spec->octo && (spec->type == 'X' || spec->type == 'x') && !num)
	//	return (0);
	//if (spec->octo && (spec->type == 'o') && !num && !spec->prec)
	//	return (0);
	s = print_pointer((unsigned long long int)p, spec);
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
//		if (spec->type == 'X' && spec->octo && spec->zero)
//			str[1] = 'X';
//		if (spec->type == 'x' && spec->octo && spec->zero)
//			str[1] = 'x';
		while (k >= 0)
		{
			str[i] = s[k];
			i--;
			k--;
		}
		ft_putstr(str);
		if (ft_strlen(s))
			free(s);
		free(str);
		return(len);
	}
	//if (spec->type == 'X' && spec->octo && spec->zero)
	//	s[1] = 'X';
	ft_putstr(s);
	if (ft_strlen(s))
		free(s);
	return (len);
}
