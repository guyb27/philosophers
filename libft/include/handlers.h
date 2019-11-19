/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handlers.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 06:55:06 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:12:09 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H
# include "ft_printf.h"

typedef struct s_printf	t_printf;
typedef struct s_flags	t_flags;
typedef struct			s_handlers {
	char				conv;
	t_printf				*(*fct_handle)(t_flags*, va_list);
}						t_handlers;

t_printf					*pf_handle(char **str, va_list args, int i);
t_printf					*pf_handle_percent(t_flags *spec, va_list args);
t_printf					*pf_handle_char(t_flags *spec, va_list args);
t_printf					*pf_handle_str(t_flags *spec, va_list args);
t_printf					*pf_handle_p(t_flags *spec, va_list args);
t_printf					*pf_handle_signed_int(t_flags *spec,
		va_list args);
t_printf					*pf_handle_unsigned_int(t_flags *spec,
		va_list args);
t_printf					*pf_handle_hex(t_flags *spec, va_list args);
t_printf					*pf_handle_oct(t_flags *spec, va_list args);
t_printf					*pf_handle_float(t_flags *spec, va_list args);
t_printf					*pf_zeroprec(t_flags *spec);
void						pf_utils_norme(char **rst, int *i, char *tmp);

#endif
