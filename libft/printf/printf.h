/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 19:13:03 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/01 22:00:19 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include <stdint.h>
# include <limits.h>
# include "../libft.h"

# define USE_ALT 1
# define PAD_0S 2
# define PAD_RT 4
# define SPC_POS 8
# define PLS_POS 16
# define PREC 32
# define WID 64
# define LEN 128

# define HAS_ALT USE_ALT
# define ALL PAD_RT | WID | PREC
# define IS_NUM PAD_0S | LEN
# define IS_SGND SPC_POS | PLS_POS

typedef unsigned char	t_byte;

typedef struct			s_strtoint
{
	char	*key;
	int		value;
}						t_strtoint;

typedef enum			e_lengths
{
	chrs,
	shrts,
	ints,
	longs,
	llongs,
	mxmms,
	szts,
}						t_lengths;

typedef struct			s_sizes
{
	t_lengths	length;
	int			width;
	int			precision;
	t_byte		opts;
}						t_sizes;

typedef va_list			t_varargs;

typedef int				(*t_putter)(t_varargs, t_sizes *);

typedef struct			s_dispatch
{
	t_putter	put;
	char		*chrs;
	t_byte		flags;
}						t_dispatch;

typedef enum			e_arg
{
	alternate,
	zero_pad,
	right_pad,
	space_pos,
	plus_pos,
	precise,
	min_width,
	END = min_width + 10,
}						t_arg;

char					*fluff_int(char *bare, t_sizes *sizes);
char					*fluff_uint(char *bare, t_sizes *sizes, char *pre);
char					*fluff_string(char *bare, t_sizes *sizes);
wchar_t					*fluff_wstring(wchar_t *bare, t_sizes *sizes);
void					adjust_sizes(t_sizes *szs, char *pre, char *bare);
uintmax_t				unsgnd_bounds_check(uintmax_t num, t_sizes *szs);
intmax_t				sgnd_bounds_check(intmax_t num, t_sizes *szs);
char					*clear_0(char *to_print, t_sizes *szs);
char					*prepend(char *bare, char *zeros, char *pre);

int						find_min_width(const char **fmt, va_list av,
							t_sizes *sizes);
int						find_precision(const char **fmt, va_list av);
size_t					find_length(const char **fmt);
void					fill_sizes(const char **fmt, t_sizes *szs, char *args,
							va_list av);
int						print_arg(const char **fmt, va_list av, t_sizes *szs);

char					*ft_uimtoa_base(uintmax_t n, int base);
char					*ft_imtoa(intmax_t n);
int						nput_percent(va_list av, t_sizes *sizes);
int						nput_pointer(va_list av, t_sizes *sizes);
int						nput_char(va_list av, t_sizes *sizes);
int						nput_wchar(va_list av, t_sizes *sizes);
int						nput_wchar_fake(va_list av, t_sizes *sizes);
int						nput_string(va_list av, t_sizes *sizes);
int						nput_wstring(va_list av, t_sizes *sizes);
int						nput_sgnd_dec(va_list av, t_sizes *sizes);
int						nput_unsgnd_dec(va_list av, t_sizes *sizes);
int						nput_oct(va_list av, t_sizes *sizes);
int						nput_hex_low(va_list av, t_sizes *sizes);
int						nput_hex_up(va_list av, t_sizes *sizes);

int						ft_printf(const char *fmt, ...);

int						color_code(char *color);
int						change_color(const char **fmt, va_list av);
void					cleanup(void);

t_dispatch				g_dsp[12];
intmax_t				g_sbounds[7][2];
uintmax_t				g_ubounds[7][2];
t_strtoint				g_colors[9];

#endif
