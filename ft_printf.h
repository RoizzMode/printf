/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:43:36 by lschambe          #+#    #+#             */
/*   Updated: 2019/02/07 16:15:29 by lschambe         ###   ########.fr       */
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

void	ft_printf(const char *format, ...);
void	initialize(t_spec *spec);
int	parse_spec(t_spec *spec, char *s);
void	print_numb(t_spec *spec, int num);
void	print_char(t_spec *spec, char c);
void	print_string(t_spec *spec, char *s);
void	print_point(t_spec *spec, char *p);
