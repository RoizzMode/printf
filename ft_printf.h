/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:43:36 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/11 14:52:05 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
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

int	ft_printf(const char *format, ...);
void	initialize(t_spec *spec);
int	parse_spec(t_spec *spec, char *s);
int	print_numb(t_spec *spec, int num);
int	print_char(t_spec *spec, char c);
int	print_string(t_spec *spec, char *s);
int	print_point(t_spec *spec, char *p);
