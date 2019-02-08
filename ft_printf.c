/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:58:28 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/08 18:23:38 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	num_len(int num)
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

int	parse_spec(t_spec *spec, char *s)
{
	int i;

	i = 0;
	while (!(s[i] == '\0' || s[i] == ' ') && spec->type == 0)
	{
		if (s[i] == '-')
			spec->minu = 1;
		if (s[i] == '+')
			spec->plu = 1;
		if (s[i] == ' ')
			spec->spac = 1;
		if (s[i] == '#')
			spec->octo = 1;
		if (s[i] == '0' && !((s[i - 1] >= '0' && s[i - 1] <= '9') || s[i - 1] == '.'))
			spec->zero = 1;
		if (s[i] >= '1' && s[i] <= '9')
		{
			spec->widt = ft_atoi(s + i);
			i += num_len(spec->widt);
		}
		if (s[i] == '.')
		{
			spec->prec = ft_atoi(s + i + 1);
			i += num_len(spec->prec) + 1;
		}
		if (s[i] == 'c' || s[i] == 'd' || s[i] == 'f' || s[i] == 'o'|| s[i] == 'u'||
				s[i] == 'x'|| s[i] == 'X'|| s[i] == 's'|| s[i] == 'p'|| s[i] == 'i'
				|| (s[i] == '%' && i != 0))
			spec->type = s[i];
		if (s[i] == 'l' && s[i + 1] == 'l')
		{
			spec->size = 'b';
			i += 2;
			continue;
		}
		if (s[i] == 'h' && s[i + 1] == 'h')
		{
			spec->size = 's';
			i += 2;
			continue;
		}
		if (s[i] == 'h' || s[i] == 'l' || s[i] == 'L')
			spec->size = s[i];
		i++;
	}
	return (i);
}

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

void	initialize(t_spec *spec)
{
	spec->minu = 0;
	spec->plu = 0;
	spec->spac = 0;
	spec->octo = 0;
	spec->zero = 0;
	spec->widt = 0;
	spec->prec = -1;
	spec->size = 0;
	spec->type = 0;
}
/*void	ft_printf(const char *format, ...)
{
	va_list ap;
	char *s;
//	int a;

	s = (char*)format;
	va_start(ap, format);
	//a = va_arg(ap, int);
	//printf("%d", a);

	va_end(ap);
}*/

void	ft_printf(const char *format, ...)
{
	int i;
	t_spec *spec;
	va_list ap;

	va_start(ap, format);
	i = 0;
	spec = (t_spec *)malloc(sizeof(t_spec));
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			initialize(spec);
			i += parse_spec(spec, (char *)(format));
			//print_spec(spec);
			if (spec->type == 'd' || spec->type == 'i' || spec->type == 'o'
					|| spec->type == 'u' ||spec->type == 'x' ||spec->type == 'X')
				print_numb(spec, va_arg(ap, int));
			if (spec->type == 'c')
				print_char(spec, va_arg(ap, int));
			if (spec->type == 's')
				print_string(spec, va_arg(ap, char*));
			if (spec->type == 'p')
				print_point(spec, va_arg(ap, char*));
		}
		else
			ft_putchar(format[i++]);
	}
	va_end(ap);
}

int main()
{
	printf("%-5.6s", "\0w");
	printf("\n");
	ft_printf("%-5.6s", "\0w");
	//printf("%d", num_len(123));
	return (0);
}
