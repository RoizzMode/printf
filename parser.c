/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:54:46 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/04 19:16:30 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_spec(t_spec *spec)
{
	printf("\n");
	if (spec->minu)
		printf("Minus: %d\n", spec->minu);
	if (spec->plu)
		printf("Plus: %d\n", spec->plu);
	if (spec->spac)
		printf("Space: %d\n", spec->spac);
	if (spec->octo)
		printf("Octopus: %d\n", spec->octo);
	if (spec->zero)
		printf("Zero: %d\n", spec->zero);
	if (spec->widt)
		printf("Width: %d\n", spec->widt);
	if (spec->prec > -1)
		printf("Precision: %d\n", spec->prec);
	if (spec->type)
		printf("Type: %c\n", spec->type);
	if (spec->size)
		printf("Size: %c\n", spec->size);
}

int		num_len(int64_t num)
{
	int i;

	i = 1;
	while (num / 10 > 0)
	{
		i++;
		num /= 10;
	}
	return (i);
}

int		help_parse(t_spec *spec, char *s, int i)
{
	if ((s[i] == '-' || s[i] == '+' || s[i] == ' ' || s[i] == '#' ||
			s[i] == '0') && !(spec->widt) && (spec->prec < 0)
			&& !(spec->size) && !(spec->type))
	{
		if (s[i] == '-')
			spec->minu = 1;
		if (s[i] == '+')
			spec->plu = 1;
		if (s[i] == ' ')
			spec->spac = 1;
		if (s[i] == '#')
			spec->octo = 1;
		if (s[i] == '0')
			spec->zero = 1;
		return (1);
	}
	return (0);
}

int		help_parse_sizes(t_spec *spec, char *s, int i)
{
	if (s[i] == 'l' && s[i + 1] == 'l' &&
			!(spec->size) && !(spec->type))
	{
		spec->size = 'b';
		i++;
		return (i);
	}
	else if (s[i] == 'h' && s[i + 1] == 'h' &&
			!(spec->size) && !(spec->type))
	{
		spec->size = 's';
		i++;
		return (i);
	}
	else if ((s[i] == 'h' || s[i] == 'l' || s[i] == 'L')
			&& !(spec->size) && !(spec->type))
	{
		spec->size = s[i];
		return (i);
	}
	return (0);
}

int		parse_cycle(t_spec *spec, char *s, int i)
{
	int d;

	if (help_parse(spec, s, i))
		return (i);
	else if (s[i] >= '1' && s[i] <= '9' && !(spec->widt)
			&& (spec->prec < 0) && !(spec->size) && !(spec->type))
	{
		spec->widt = ft_atoi(s + i);
		i = i + num_len(spec->widt) - 1;
	}
	else if (s[i] == '.')
	{
		if (s[i + 1] >= '0' && s[i + 1] <= '9')
		{
			spec->prec = ft_atoi(s + i + 1);
			i += num_len(spec->prec);
		}
		else
			spec->prec = 0;
	}
	else if ((d = help_parse_sizes(spec, s, i)))
		i = d;
	else if (s[i] >= 0 && s[i] <= 127 && i > 0)
		spec->type = s[i];
	return (i);
}

int		parse_spec(t_spec *spec, char *s)
{
	int i;

	i = 0;
	while (spec->type == 0 && s[i] != '\0')
	{
		i = parse_cycle(spec, s, i);
		i++;
	}
	print_spec(spec);
	if (!spec->type)
		return (0);
	return (i);
}
