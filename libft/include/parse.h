/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:48:11 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:48:11 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
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
