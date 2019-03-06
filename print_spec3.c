/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:32:56 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:34:20 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*help_itoa(char *oct, t_spec *spec, int i, int check)
{
	if (check < 0 && !((spec->minu || spec->zero) && spec->widt > i))
		oct[0] = '-';
	if (check > 0 && spec->plu && !((spec->minu || spec->zero)
				&& spec->widt > i))
		oct[0] = '+';
	if (check > 0 && spec->spac && !((spec->minu || spec->zero)
				&& spec->widt > i))
		oct[0] = ' ';
	return (oct);
}

int			help_len(int len, t_spec *spec, long long unnum)
{
	if (len < spec->prec)
		len = spec->prec - 1;
	if ((unnum < 0 || spec->plu || spec->spac))
		len++;
	return (len);
}

char		*signed_itoa(long long int num, t_spec *spec)
{
	char			*oct;
	int				len;
	int				check;
	long long int	unnum;
	int				i;

	i = 0;
	if (!spec->prec && !num && !spec->octo)
		return ("");
	change_spec(spec);
	unnum = help_cast(num, spec);
	len = num_len_signed(unnum);
	check = help_check(unnum);
	len = help_len(len, spec, unnum);
	oct = (char*)malloc(sizeof(char) * len + 2);
	if (!oct)
		return (NULL);
	while (i < len)
		oct[i++] = '0';
	oct[len + 1] = '\0';
	oct[len--] = (unnum % 10) * check + '0';
	while (unnum /= 10)
		oct[len--] = (unnum % 10) * check + '0';
	oct = help_itoa(oct, spec, i, check);
	return (oct);
}

char		*get_str_char(t_spec *spec, char *str, int len, char c)
{
	if (spec->prec > 0)
		str[len - spec->prec - 1] = c;
	else if (spec->minu || spec->zero)
		str[0] = c;
	else
		str[len - spec->widt + 1] = c;
	return (str);
}
