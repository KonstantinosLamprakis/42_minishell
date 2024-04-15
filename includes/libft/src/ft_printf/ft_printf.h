/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:12:19 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:32:03 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../ft_char/ft_char.h" // ft_isdigit
# include "../ft_put/ft_put.h"	/*	ft_printchar, ft_printstr, ft_printnbr,
									ft_printnbr_base */
# include "../ft_string/ft_string.h" // ft_strlen
# include "../ft_conversion/ft_conversion.h" // ft_itoa, ft_utoa, ft_htoa

# include <limits.h> // INT_MIN
# include <stdarg.h> // va_start & va_arg & va_copy & va_end
# include <stdlib.h> // malloc & free
# include <unistd.h> // write

typedef struct s_flag
{
	int	f_offset;
	int	alt;
	int	la_flag;
	int	sign;
	int	spc;
	int	zero;
	int	fw_v;
	int	p_flag;
	int	p_v;
}		t_flag;

/*		Main Function		*/
int		ft_printf(const char *str, ...);

/*		Parser	Flag(s) -> Width -> Precision -> Type			*/
int		ft_parse_flag1(va_list ap, const char *str, t_flag *flag);
int		ft_parse_flag2(va_list ap, const char *str, t_flag *flag);
int		ft_parse_width(va_list ap, const char *str, t_flag *flag);
int		ft_parse_precision(va_list ap, const char *str, t_flag *flag);
int		ft_parse_type(va_list ap, const char *str, t_flag *flag);

/*			'c' & 's' conversion handling		*/
int		ft_printchar(int c, t_flag *flag);
int		ft_printstr(char *s, t_flag *flag);

/*			'd' & 'i' conversion handling		*/
int		ft_printnbr(int n, t_flag *flag);

/*			'p' conversion handling				*/
int		ft_printptr(size_t n, t_flag *flag);

/*			'x' & 'X' conversion handling		*/
int		ft_printhex(unsigned int n, t_flag *flag, int lower);

/*			'u' conversion handling				*/
int		ft_printunbr(unsigned int n, t_flag *flag);

/*			Flag utils							*/
t_flag	*t_flag_new(void);
void	ft_reset_flag(t_flag *flag);

/*			Free utils							*/
int		ft_va_quit(va_list ap);
int		ft_free_flag(t_flag *flag);

/*			Nbr Utils							*/
int		ft_get_intlog_a(int n, int a);
int		ft_max_int(int a, ...);
int		ft_min_int(int argc, ...);

int		ft_print_width(t_flag *flag);

#endif
