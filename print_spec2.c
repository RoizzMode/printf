/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:32:27 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:32:51 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_negative(long long int num, t_spec *spec)
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

long long	help_cast(long long num, t_spec *spec)
{
	long long unnum;

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
	return (unnum);
}

void		change_spec(t_spec *spec)
{
	if (spec->plu && spec->spac)
		spec->spac = 0;
	if (spec->minu && spec->zero)
		spec->zero = 0;
}

int			num_len_signed(long long unnum)
{
	int len;

	len = 0;
	while (unnum / 10)
	{
		len++;
		unnum /= 10;
	}
	return (len);
}

int			help_check(long long unnum)
{
	int check;

	check = 1;
	if (unnum < 0)
		check = -1;
	return (check);
}
