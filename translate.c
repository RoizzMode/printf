/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:11:40 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/14 18:06:11 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *dec_to_oct(unsigned long long int num, t_spec *spec)
{
	char  *oct;
	int len;
	int check;
	unsigned long long int unnum;
	int i = 0;

	len = 0;
	if (spec->size == 'l')
		unnum = (unsigned long int)num;
	else if (spec->size == 's')
		unnum = (unsigned char)num;
	else if (spec->size == 'h')
		unnum = (unsigned short int)num;
	else if (spec->size == 'b')
		unnum = num;
	else
		unnum = (unsigned int)num;
	while (unnum / 8)
	{
		len++;
		unnum /= 8;
	}
	if (spec->size == 'l')
		unnum = (unsigned long int)num;
	else if (spec->size == 's')
		unnum = (unsigned char)num;
	else if (spec->size == 'h')
		unnum = (unsigned short int)num;
	else if (spec->size == 'b')
		unnum = num;
	else
		unnum = (unsigned int)num;
	check = 1;
	if (len < spec->prec)
		len = spec->prec - 1;
	if (spec->octo && num)
	{
		if (len < spec->widt)
			len = spec->widt - 1;
		else
			len++;
	}
	oct = (char*)malloc(sizeof(char) * len + 2);
	if (!oct)
		return (NULL);
	while (i < len)
		oct[i++] = '0';
	oct[len + 1] = '\0';
	oct[len--] = (unnum % 8) * check + '0';
	while (unnum /= 8)
		oct[len--] = (unnum % 8) * check + '0';
	//oct[len + 1] = '\0';
	//oct[len--] = (unnum % 8) * check + '0';
	//while (unnum /= 8)
	//	oct[len--] = (check * unnum % 8 + '0');
	if (spec->octo && num)
		oct[0] = '0';
	return (oct);
}

/*char *dec_to_hex(unsigned long long int num, int flag, char size)
{
	char  *hex;
	int len;
	unsigned long long int unnum;
	int check;

	len = 0;
	//printf("%llu\n", num);
	if (size == 'l')
		unnum = (unsigned long int)num;
	else if (size == 's')
		unnum = (unsigned char)num;
	else if (size == 'h')
		unnum = (unsigned short int)num;
	else if (size == 'b')
		unnum = num;
	else
		unnum = (unsigned int)num;
	//unnum = num;
	while (unnum / 16)
	{
		len++;
		unnum /= 16;
	}
	check = 1;
	//unnum = num;
	if (size == 'l')
		unnum = (unsigned long int)num;
	else if (size == 's')
		unnum = (unsigned char)num;
	else if (size == 'h')
		unnum = (unsigned short int)num;
	else if (size == 'b')
		unnum = num;
	else
		unnum = (unsigned int)num;
	if (flag && num)
		len += 2;
	hex = (char*)malloc(sizeof(char) * len + 2);
	if (!hex)
		return (NULL);
	hex[len + 1] = '\0';
	if (unnum % 16 > 9)
		hex[len--] = (unnum % 16) * check + 'a' - 10;
	else
		hex[len--] = (unnum % 16) * check + '0';
	while (unnum /= 16)
	{
		if (unnum % 16 > 9)
			hex[len--] = (unnum % 16) * check + 'a' - 10;
		else
			hex[len--] = (unnum % 16) * check + '0';
	}
	if (flag && num)
	{
		hex[1] = 'x';
		hex[0] = '0';
	}
	return (hex);
}*/

char *dec_to_hex(unsigned long long int num, t_spec *spec)
{
	char  *hex;
	int len;
	unsigned long long int unnum;
	int check;
	int i = 0;

	len = 0;
	if (spec->size == 'l')
		unnum = (unsigned long int)num;
	else if (spec->size == 's')
		unnum = (unsigned char)num;
	else if (spec->size == 'h')
		unnum = (unsigned short int)num;
	else if (spec->size == 'b')
		unnum = num;
	else
		unnum = (unsigned int)num;
	while (unnum / 16)
	{
		len++;
		unnum /= 16;
	}
	check = 1;
	if (spec->size == 'l')
		unnum = (unsigned long int)num;
	else if (spec->size == 's')
		unnum = (unsigned char)num;
	else if (spec->size == 'h')
		unnum = (unsigned short int)num;
	else if (spec->size == 'b')
		unnum = (unsigned long long int)num;
	else
		unnum = (unsigned int)num;
	if (len < spec->prec)
		len = spec->prec - 1;
	if (spec->octo && num)
	{
		if (len < spec->widt)
			len = spec->widt - 1;
		else
			len += 2;
	}
	hex = (char*)malloc(sizeof(char) * len + 2);
	if (!hex)
		return (NULL);
	while (i < len)
		hex[i++] = '0';
	hex[len + 1] = '\0';
	if (unnum % 16 > 9)
		hex[len--] = (unnum % 16) * check + 'a' - 10;
	else
		hex[len--] = (unnum % 16) * check + '0';
	while (unnum /= 16)
	{
		if (unnum % 16 > 9)
			hex[len--] = (unnum % 16) * check + 'a' - 10;
		else
			hex[len--] = (unnum % 16) * check + '0';
	}
	if (spec->octo && num)
	{
		hex[1] = 'x';
		hex[0] = '0';
	}
	return (hex);
}

char *dec_to_heX(unsigned long long int num, t_spec *spec)
{
	char  *hex;
	int len;
	unsigned long long int unnum;
	int check;
	int i;

	len = 0;
	i = 0;
	if (spec->size == 'l')
		unnum = (unsigned long int)num;
	else if (spec->size == 's')
		unnum = (unsigned char)num;
	else if (spec->size == 'h')
		unnum = (unsigned short int)num;
	else if (spec->size == 'b')
		unnum = num;
	else
		unnum = (unsigned int)num;
	while (unnum / 16)
	{
		len++;
		unnum /= 16;
	}
	check = 1;
	if (spec->size == 'l')
		unnum = (unsigned long int)num;
	else if (spec->size == 's')
		unnum = (unsigned char)num;
	else if (spec->size == 'h')
		unnum = (unsigned short int)num;
	else if (spec->size == 'b')
		unnum = (unsigned long long int)num;
	else
		unnum = (unsigned int)num;
	if (len < spec->prec)
		len = spec->prec - 1;
	if (spec->octo && num)
	{
		if (len < spec->widt)
			len = spec->widt - 1;
		else
			len += 2;
	}
	hex = (char*)malloc(sizeof(char) * len + 2);
	if (!hex)
		return (NULL);
	while (i < len)
		hex[i++] = '0';
	hex[len + 1] = '\0';
	if (unnum % 16 > 9)
		hex[len--] = (unnum % 16) * check + 'A' - 10;
	else
		hex[len--] = (unnum % 16) * check + '0';
	while (unnum /= 16)
	{
		if (unnum % 16 > 9)
			hex[len--] = (unnum % 16) * check + 'A' - 10;
		else
			hex[len--] = (unnum % 16) * check + '0';
	}
	if (spec->octo && num)
	{
		hex[1] = 'X';
		hex[0] = '0';
	}
	return (hex);
}
