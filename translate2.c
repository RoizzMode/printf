/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:30:24 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:31:01 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	casted_un(unsigned long long num, t_spec *spec)
{
	unsigned long long int unnum;

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
	return (unnum);
}

int					num_len_un(unsigned long long unnum)
{
	int len;

	len = 1;
	while (unnum / 10)
	{
		len++;
		unnum /= 10;
	}
	return (len);
}

char				*unsigned_itoa(unsigned long long int num, t_spec *spec)
{
	char						*oct;
	int							len;
	int							check;
	unsigned long long int		unnum;
	int							i;

	i = 0;
	if (!spec->prec && !num && !spec->octo)
		return ("");
	unnum = casted_un(num, spec);
	len = num_len_un(unnum);
	check = 1;
	if (len < spec->prec)
		len = spec->prec - 1;
	oct = (char*)malloc(sizeof(char) * len + 2);
	if (!oct)
		return (NULL);
	while (i < len)
		oct[i++] = '0';
	oct[len + 1] = '\0';
	oct[len--] = (unnum % 10) * check + '0';
	while (unnum /= 10)
		oct[len--] = (unnum % 10) * check + '0';
	return (oct);
}

char				*get_oct(char *oct, unsigned long long unnum, int len)
{
	oct[len--] = (unnum % 8) + '0';
	while (unnum /= 8)
		oct[len--] = (unnum % 8) + '0';
	return (oct);
}

char				*dec_to_oct(unsigned long long int num, t_spec *spec)
{
	char					*oct;
	int						len;
	unsigned long long int	unnum;
	int						i;

	i = 0;
	if (!spec->prec && !num && !spec->octo)
		return ("");
	unnum = casted_un(num, spec);
	len = num_len_un(unnum);
	if (len < spec->prec)
		len = spec->prec - 1;
	else if (spec->octo && num)
		len++;
	oct = (char*)malloc(sizeof(char) * len + 2);
	if (!oct)
		return (NULL);
	while (i < len)
		oct[i++] = '0';
	oct[len + 1] = '\0';
	oct = get_oct(oct, unnum, len);
	if (spec->octo && num)
		oct[0] = '0';
	return (oct);
}
