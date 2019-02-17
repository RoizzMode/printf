/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:58:28 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/17 15:26:36 by lschambe         ###   ########.fr       */
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
	while (spec->type == 0 && s[i] != '\0')
	{
		if (s[i] == '-' && !(spec->widt) && (spec->prec < 0) && !(spec->size) && !(spec->type))
			spec->minu = 1;
		else if(s[i] == '+' && !(spec->widt) && (spec->prec < 0) && !(spec->size) && !(spec->type))
			spec->plu = 1;
		else if (s[i] == ' ' && !(spec->widt) && (spec->prec < 0) && !(spec->size) && !(spec->type))
			spec->spac = 1;
		else if (s[i] == '#' && !(spec->widt) && (spec->prec < 0) && !(spec->size) && !(spec->type))
			spec->octo = 1;
		else if (s[i] == '0' /*&& !((s[i - 1] >= '0' && s[i - 1] <= '9') || s[i - 1] == '.')*/
				&& !(spec->widt) && (spec->prec < 0) && !(spec->size) && !(spec->type))
			spec->zero = 1;
		else if (s[i] >= '1' && s[i] <= '9' && !(spec->widt) && (spec->prec < 0)
				&& !(spec->size) && !(spec->type))
		{
			spec->widt = ft_atoi(s + i);
			i =i + num_len(spec->widt) - 1;
			//printf("%d", i);
		}
		//else if (s[i] == '.' && (spec->prec < 0) && !(spec->size) && !(spec->type))
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
		//if (s[i] == 'c' || s[i] == 'd' || s[i] == 'f' || s[i] == 'o'|| s[i] == 'u'||
		//		s[i] == 'x'|| s[i] == 'X'|| s[i] == 's'|| s[i] == 'p'|| s[i] == 'i'
		//		|| (s[i] == '%' && i != 0))
		//	spec->type = s[i];
		else if (s[i] == 'l' && s[i + 1] == 'l' && !(spec->size) && !(spec->type))
		{
			spec->size = 'b';
			i += 2;
			continue;
		}
		else if (s[i] == 'h' && s[i + 1] == 'h' && !(spec->size) && !(spec->type))
		{
			spec->size = 's';
			i += 2;
			continue;
		}
		else if ((s[i] == 'h' || s[i] == 'l' || s[i] == 'L') && !(spec->size) && !(spec->type))
			spec->size = s[i];
		else if (s[i] >= 0 && s[i] <= 127 && i > 0)
		{
			spec->type = s[i];
		}
		i++;
		//printf("%c ", s[i]);
	}
	if (!spec->type)
		return (0);
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

int	ft_printf(const char *format, ...)
{
	int i;
	t_spec *spec;
	va_list ap;
	int k;
	int parsed;

	va_start(ap, format);
	i = 0;
	k = 0;
	spec = (t_spec *)malloc(sizeof(t_spec));
	initialize(spec);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && (parsed = parse_spec(spec, (char *)(format + i))))
		{
			i += parsed;
			//print_spec(spec);
			if (spec->type == 'd' || spec->type == 'i')
				k += print_signed_numb(spec, va_arg(ap, long long int));
			else if (spec->type == 'o' || spec->type == 'u' ||
					spec->type == 'x' || spec->type == 'X')
				k += print_unsigned_numb(spec, va_arg(ap, unsigned long long int));
			else if (spec->type == 'c')
				k += print_char(spec, va_arg(ap, int));
			else if (spec->type == 's')
			{
				k += print_string(spec, va_arg(ap, char*));
			}
			else if (spec->type == 'p')
				k += print_point(spec, va_arg(ap, void*));
			else if (spec->type == 'f')
				k += print_float(spec, va_arg(ap, long double));
			else
				k += print_char(spec, spec->type);
			initialize(spec);
		}
		else
		{
			ft_putchar(format[i++]);
			k++;
		}
	}
	va_end(ap);
	return (k);
}

int main()
{
//	unsigned long long int ull = 9223372036854775807; //9223372036854775807;
//	unsigned long int ul = 4294967295; //4294967295
//	unsigned short int us = 65535; //65535
//	unsigned char uc = 255; //255
//	unsigned int ui = 4294967295;
//	printf("%#llo\n", ull);
//	ft_printf("%#llo\n", ull);
//	printf("%#lo\n", ul);
//	ft_printf("%#lo\n", ul);
//	printf("%#ho\n", us);
//	ft_printf("%#ho\n", us);
//	long long int lli = -42;
	double d = 4.3123;
	long double ld = 813.312342342543533454454675678686752344543353456456556786787978923423423423423432432456768678789798;
	printf("%d" ,printf("Unix: %f %.50Lf\n", d, ld));
	printf("%d" , ft_printf("My  : %f %Lf\n", d, ld));
	return (0);
}
