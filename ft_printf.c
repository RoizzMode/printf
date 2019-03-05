/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:58:28 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/05 20:34:26 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <math.h>

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

int		help_cycle(t_spec *spec, va_list ap)
{
	int k;

	k = 0;
	if (spec->type == 'd' || spec->type == 'i')
		k += print_signed_numb(spec, va_arg(ap, long long int));
	else if (spec->type == 'o' || spec->type == 'u' ||
			spec->type == 'x' || spec->type == 'X')
		k += print_un_numb(spec, va_arg(ap, unsigned long long int));
	else if (spec->type == 'c')
		k += print_char(spec, va_arg(ap, int));
	else if (spec->type == 's')
		k += print_string(spec, va_arg(ap, char*));
	else if (spec->type == 'p')
		k += print_point(spec, va_arg(ap, void*));
	else if (spec->type == 'f' && spec->size == 'L')
		k += print_long_double(spec, va_arg(ap, long double));
	else if (spec->type == 'f')
		k += print_double(spec, va_arg(ap, double));
	else if (spec->type == '%')
		k += print_proc(spec, spec->type);
	else
		k += print_char(spec, spec->type);
	return (k);
}

int		cycle(t_spec *spec, const char *s, va_list ap)
{
	int k;
	int i;
	int parsed;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%' && (parsed = parse_spec(spec, (char *)(s + i))))
		{
			i += parsed;
			k += help_cycle(spec, ap);
			initialize(spec);
		}
		else
		{
			ft_putchar(s[i++]);
			k++;
		}
	}
	return (k);
}

int		ft_printf(const char *format, ...)
{
	t_spec	*spec;
	va_list	ap;
	int		k;

	va_start(ap, format);
	k = 0;
	spec = (t_spec *)malloc(sizeof(t_spec));
	initialize(spec);
	k = cycle(spec, format, ap);
	free(spec);
	va_end(ap);
	return (k);
}

int		main()
{
	long int d = 64564;
//	short int s = 128;
//	long int l = 134454;
//	char c = 22;
//	unsigned int u = 31243;
//	char *s = "qwerty";
//	char c = 0;
//	char *s = "qwerty";
//	int d = 122;
//	int *p = &d;
//	long double f = -0.0000000;

//	printf("%d ", printf("%+15.20hd %+020.15lld %+0.ld %+010hhd %.Lf\n", s, d, l, c, f));
//	printf("%d ", ft_printf("%+15.20hd %+020.15lld %+0.ld %+010hhd %.Lf\n", s, d, l, c, f));
	printf("%d", printf("%+0ld\n", d));
	printf("%d", ft_printf("%+0ld\n", d));
	return (0);
}
