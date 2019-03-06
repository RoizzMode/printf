/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print__excs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:22:39 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:23:10 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		read_base(double num)
{
	unsigned char	*casted;
	int				i;
	int				one;
	int				null;

	casted = (unsigned char *)&num;
	one = 0;
	null = 0;
	i = 6;
	while (i > -1)
		if (casted[7] & (1 << i--))
			one = 1;
		else
			null = 1;
	i = 7;
	while (i > 3)
		if (casted[6] & (1 << i--))
			one = 1;
		else
			null = 1;
	if ((one && !null) || (!one && null))
		return ((one && !null) ? (1) : (0));
	return (-1);
}

int		help_mantiss(int null, int one)
{
	if (one && !null)
		return (1);
	if (!one && null)
		return (0);
	return (-1);
}

int		read_mantiss(double num, int i)
{
	unsigned char	*casted;
	int				j;
	int				one;
	int				null;

	casted = (unsigned char *)&num;
	one = 0;
	null = 0;
	i = 3;
	while (i > -1)
		if (casted[6] & (1 << i--))
			one = 1;
		else
			null = 1;
	i = 5;
	while (i-- > 1)
	{
		j = 7;
		while (j > -1)
			if (casted[i] & (1 << j--))
				one = 1;
			else
				null = 1;
	}
	return (help_mantiss(null, one));
}

int		read_sign(double num)
{
	unsigned char *casted;

	casted = (unsigned char*)&num;
	if (casted[7] & (1 << 7))
		return (1);
	return (0);
}
