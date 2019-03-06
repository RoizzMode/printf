/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:31:08 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:31:28 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					get_len_hexx(int len, t_spec *spec, unsigned long long num)
{
	if (len < spec->prec)
		len = spec->prec - 1;
	if (spec->octo && num)
		len += 2;
	return (len);
}

char				*get_hex(char *hex, unsigned long long unnum, int len)
{
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
	return (hex);
}
