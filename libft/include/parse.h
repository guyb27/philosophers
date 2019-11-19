/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flags.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 18:26:25 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 11:34:32 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "ft_printf.h"

enum			e_flags {hash, zero, minus, plus, space, maj_l};
enum			e_size {none, hh, h, l, ll, j, z};

typedef struct	s_flags {
	int			flags[6];
	int			width;
	int			prec;
	int			size;
	char		conv;
}				t_flags;

t_flags			*pf_parse(char *arg);

int				pf_is_conv(const char c);
int				pf_is_size(const char c);
int				pf_is_flag(const char c);
int				pf_is_valid(const char c);

#endif
