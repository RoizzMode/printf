/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:43:36 by lschambe          #+#    #+#             */
/*   Updated: 2019/03/06 14:34:16 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"

typedef struct		s_spec
{
	int		minu;
	int		plu;
	int		spac;
	int		octo;
	int		zero;
	int		widt;
	int		prec;
	char	size;
	char	type;
}					t_spec;

typedef struct		s_float
{
	int64_t		before_p;
	double		after_p;
}					t_float;

typedef struct		s_dfloat
{
	int64_t		before_p;
	long double	after_p;
}					t_dfloat;

int					ft_printf(const char *format, ...);
void				initialize(t_spec *spec);
int					parse_spec(t_spec *spec, char *s);
int					print_signed_numb(t_spec *spec, long long int num);
int					print_un_numb(t_spec *spec, unsigned long long int num);
int					print_char(t_spec *spec, char c);
int					print_string(t_spec *spec, char *s);
int					print_point(t_spec *spec, void *p);
int					print_double(t_spec *spec, double num);
int					print_long_double(t_spec *spec, long double num);
char				*dec_to_oct(unsigned long long int num, t_spec *spec);
char				*dec_to_hex(unsigned long long int num, t_spec *spec);
char				*dec_to_hexx(unsigned long long int num, t_spec *spec);
char				*unsigned_itoa(unsigned long long int num, t_spec *spec);
char				*signed_itoa(long long int num, t_spec *spec);
char				*print_pointer(unsigned long long int num, t_spec *spec);
int					num_len(int64_t num);
char				*itoa_after_p(double num, int prec);
double				round_p(double num, int prec);
int64_t				ft_pow2(int n, int64_t p);
char				*ft_itoa2(int64_t n, t_spec *spec);
int					read_base(double num);
int					read_mantiss(double num, int i);
int					read_sign(double num);
int					print_zero(double num, t_spec *spec);
int					print_inf(t_spec *spec, double num);
int					nan_inf_0(double num, t_spec *spec);
int					nan_inf_0_long(long double num, t_spec *spec);
int					print_inf_long(t_spec *spec, long double num);
int					print_zero_long(long double num, t_spec *spec);
int					read_sign_long(long double num);
int					read_mantiss_long(long double num, int i,
					int one, int null);
int					read_base_long(long double num, int i);
char				*itoa_after_p_long(long double num, int prec);
long double			round_p_long(long double num, int prec);
int					print_proc(t_spec *spec, char c);
int					help_cycle(t_spec *spec, va_list ap);
int					cycle(t_spec *spec, const char *s, va_list ap);
char				*help_itoa_after(int prec, int i);
int					ft_len(int64_t n);
int					len_after(int prec);
char				*help_itoa2(int64_t n, t_spec *spec, char *s, int len);
int					check_0(int64_t n);
char				*itoa_help_long(int prec, int i);
int					parse_cycle(t_spec *spec, char *s, int i);
int					help_parse_sizes(t_spec *spec, char *s, int i);
int					help_parse(t_spec *spec, char *s, int i);
int					num_len(int64_t num);
int					help_char(char c, int len);
void				help_string(t_spec *spec, char *s, int len);
char				*make_string(double num, t_spec *spec);
char				*help_string2(char *str, char *s, t_spec *spec, double num);
int					make_i(int minu, int i, int k);
int					make_string2(char *s, t_spec *spec, int len, double num);
int					get_len_zero_long(t_spec *spec, long double num);
int					get_lenafter_zero_long(t_spec *spec);
char				*get_zero_s_long(t_spec *spec, long double num, int len);
int					get_i_zero_long(int i, t_spec *spec, int k);
char				*get_zero_sign_long(char *str, long double num,
					t_spec *spec, char *s);
int					print_zero_widt_long(char *s, t_spec *spec, int len,
					long double num);
int					print_zero_long(long double num, t_spec *spec);
int					print_inf_widt_long(char *s, t_spec *spec, int len);
int					print_inf_long(t_spec *spec, long double num);
int					get_nan_long(t_spec *spec, int len, char *s);
int					print_nan_long(long double num, t_spec *spec);
char				*get_s_long(long double num, t_spec *spec);
void				change_spec_long(t_spec *spec);
char				*get_str_widt_long(t_spec *spec, char *s, int len);
char				*get_str_sign_long(t_spec *spec, char *str, char *s,
					long double num);
char				*help_point(t_spec *spec, char *s, int len);
int					print_point(t_spec *spec, void *p);
int					help_signed(t_spec *spec, char *s, int len, long long num);
int					get_i_signed(int i, int k, int minu);
char				*get_str_signed(t_spec *spec, char *str, long long num,
					int len);
char				*get_str_char(t_spec *spec, char *str, int len, char c);
int					help_len(int len, t_spec *spec, long long unnum);
char				*help_itoa(char *oct, t_spec *spec, int i, int check);
int					help_check(long long unnum);
void				change_spec(t_spec *spec);
long long			help_cast(long long num, t_spec *spec);
int					check_negative(long long int num, t_spec *spec);
int					help_un_numb(t_spec *spec, char *s, int len);
int					get_i_un_numb(int i, int k, int minu);
char				*get_str_un_numb(char *str, t_spec *spec);
char				*take_num(unsigned long long int num, t_spec *spec);
char				*get_str_zero2(char *s, t_spec *spec, double num, int len);
int					help_print0(double num, t_spec *spec, char *s, int len);
void				print_free(char *s, char *str);
char				*get_str_zero(char *str, char *s, t_spec *spec, double num);
int					get_i(int i, int k, int minu);
int					print_nan(t_spec *spec);
int					help_nan(t_spec *spec, char *s, int len);
int					print_inf(t_spec *spec, double num);
int					help_inf(char *s, t_spec *spec, int len);
int					help_mantiss(int null, int one);
char				*get_address(char *hex, unsigned long long unnum, int len);
char				*get_hexx(char *hex, unsigned long long unnum, int len);
char				*get_hex(char *hex, unsigned long long unnum, int len);
int					get_len_hexx(int len, t_spec *spec, unsigned long long num);
char				*get_oct(char *oct, unsigned long long unnum, int len);
int					num_len_un(unsigned long long unnum);
unsigned long long	casted_un(unsigned long long num, t_spec *spec);
int					num_len_signed(long long unnum);

#endif
