/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:25:23 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/04 20:08:32 by lschambe         ###   ########.fr       */
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
	while (unnum / 10)
	{
		len++;
		unnum /= 10;
	}
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
	if (len < spec->prec)
		len = spec->prec - 1;
	if ((unnum < 0 || spec->plu || spec->spac))
		len++;
	oct = (char*)malloc(sizeof(char) * len + 2);
	if (!oct)
		return (NULL);
	while (i < len)
		oct[i++] = '0';
	oct[len + 1] = '\0';
	oct[len--] = (unnum % 10) * check + '0';
	while (unnum /= 10)
		oct[len--] = (unnum % 10) * check + '0';
//	if (check < 0 && (!(spec->minu || spec->zero) || (spec->zero && spec->widt < (int)ft_strlen(oct) && spec->prec < 0)))
	if (check < 0  && !((spec->minu || spec->zero) && spec->widt > i))
		oct[0] = '-';
	if (check > 0 && spec->plu && !((spec->minu || spec->zero) && spec->widt > i))
		oct[0] = '+';
	if (check > 0 && spec->spac && !((spec->minu || spec->zero) && spec->widt > i))
//	if (check > 0 && spec->spac && (!(spec->minu || spec->zero) || (spec->zero && spec->widt < (int)ft_strlen(oct) && spec->prec < 0)))
		oct[0] = ' ';
//	ft_putstr(oct);
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
	s = signed_itoa(num, spec);
	len = (int)ft_strlen(s);
	//ft_putstr(s);
	//printf("|%s|", s);
	if (spec->widt >= (int)ft_strlen(s))
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
		while (k >= 0)
		{
			str[i] = s[k];
			i--;
			k--;
		}
		if (!check_negative(num, spec) && (spec->minu || spec->zero))
		{
			if (spec->prec > 0)
				str[len - spec->prec - 1] = '-';
			else if (spec->minu || spec->zero)
				str[0] = '-';
			else
				str[len - spec->widt + 1] = '-';
		}
		if (check_negative(num, spec) && spec->plu && (spec->minu || spec->zero))
		{
			//str[0] = '+';
			//printf("%d %d %d\n", spec->prec, len, (int)ft_strlen(s));
			if (spec->prec > 0)
				str[len - spec->prec - 1] = '+';
			else if (spec->minu || spec->zero)
				str[0] = '+';
				//printf("here");
			else
				str[len - spec->widt + 1] = '+';
		}
		if (check_negative(num, spec) && spec->spac && (spec->minu || spec->zero))
		{
			if (spec->prec > 0)
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

