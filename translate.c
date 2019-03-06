/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:11:40 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:31:33 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*dec_to_hex(unsigned long long int num, t_spec *spec)
{
	char					*hex;
	int						len;
	unsigned long long int	unnum;
	int						i;

	i = 0;
	if (!spec->prec && !num)
		return ("");
	unnum = casted_un(num, spec);
	len = num_len_un(unnum);
	len = get_len_hexx(len, spec, num);
	hex = (char*)malloc(sizeof(char) * len + 2);
	if (!hex)
		return (NULL);
	while (i < len)
		hex[i++] = '0';
	hex[len + 1] = '\0';
	hex = get_hex(hex, unnum, len);
	if (spec->octo && num && !((spec->zero || spec->minu) && spec->widt > i))
	{
		hex[1] = 'x';
		hex[0] = '0';
	}
	return (hex);
}

char				*get_hexx(char *hex, unsigned long long unnum, int len)
{
	if (unnum % 16 > 9)
		hex[len--] = (unnum % 16) + 'A' - 10;
	else
		hex[len--] = (unnum % 16) + '0';
	while (unnum /= 16)
	{
		if (unnum % 16 > 9)
			hex[len--] = (unnum % 16) + 'A' - 10;
		else
			hex[len--] = (unnum % 16) + '0';
	}
	return (hex);
}

char				*dec_to_hexx(unsigned long long int num, t_spec *spec)
{
	char					*hex;
	int						len;
	unsigned long long int	unnum;
	int						i;

	len = 0;
	i = 0;
	if (!spec->prec && !num)
		return ("");
	unnum = casted_un(num, spec);
	len = num_len_un(unnum);
	len = get_len_hexx(len, spec, num);
	hex = (char*)malloc(sizeof(char) * len + 2);
	if (!hex)
		return (NULL);
	while (i < len)
		hex[i++] = '0';
	hex[len + 1] = '\0';
	hex = get_hexx(hex, unnum, len);
	if (spec->octo && num && !((spec->zero || spec->minu) && spec->widt > i))
	{
		hex[1] = 'X';
		hex[0] = '0';
	}
	return (hex);
}

char				*get_address(char *hex, unsigned long long unnum, int len)
{
	hex[len + 1] = '\0';
	if (unnum % 16 > 9)
		hex[len--] = (unnum % 16) + 'a' - 10;
	else
		hex[len--] = (unnum % 16) + '0';
	while (unnum /= 16)
	{
		if (unnum % 16 > 9)
			hex[len--] = (unnum % 16) + 'a' - 10;
		else
			hex[len--] = (unnum % 16) + '0';
	}
	hex[1] = 'x';
	hex[0] = '0';
	return (hex);
}

char				*print_pointer(unsigned long long int num, t_spec *spec)
{
	char					*hex;
	int						len;
	unsigned long long int	unnum;
	int						i;

	len = 0;
	i = 0;
	unnum = num;
	while (unnum / 16)
	{
		len++;
		unnum /= 16;
	}
	unnum = num;
	if (len < spec->prec)
		len = spec->prec - 1;
	len += 2;
	hex = (char*)malloc(sizeof(char) * len + 2);
	if (!hex)
		return (NULL);
	while (i < len)
		hex[i++] = '0';
	hex = get_address(hex, unnum, len);
	return (hex);
}
