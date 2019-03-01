/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:43:36 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/01 14:35:28 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "libft/libft.h"

typedef struct s_spec
{
	int minu;
	int plu;
	int spac;
	int octo;
	int zero;
	int widt;
	int prec;
	char size;
	char type;
}				t_spec;

typedef struct s_float
{
	int64_t before_p;
	double after_p;
}				t_float;

int	ft_printf(const char *format, ...);
void	initialize(t_spec *spec);
int	parse_spec(t_spec *spec, char *s);
int	print_signed_numb(t_spec *spec, long long int num);
int	print_unsigned_numb(t_spec *spec, unsigned long long int num);
int	print_char(t_spec *spec, char c);
int	print_string(t_spec *spec, char *s);
int	print_point(t_spec *spec, void *p);
int print_double(t_spec *spec, double num);
int print_long_double(t_spec *spec, long double num);
char *dec_to_oct(unsigned long long int num, t_spec *spec);
char *dec_to_hex(unsigned long long int num, t_spec *spec);
char *dec_to_heX(unsigned long long int num, t_spec *spec);
char *unsigned_itoa(unsigned long long int num, t_spec *spec);
char *signed_itoa(long long int num, t_spec *spec);
char *print_pointer(unsigned long long int num, t_spec *spec);
int	num_len(int64_t num);
char *itoa_after_p(double num);
void round_p(t_float *tf, int prec);
int64_t		ft_pow2(int n, int64_t p);
//static int	ft_len(int64_t n);
char		*ft_itoa2(int64_t n, t_spec* spec);
