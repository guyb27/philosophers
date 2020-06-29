/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:48:11 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 13:30:46 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H
# include "ft_printf.h"

	#if __linux__
		#define intmax_t __intmax_t
		#define uintmax_t __uintmax_t
	#endif


char			*pf_strchr(const char *s, int c);
char			*pf_strdup(const char *src);
char			*pf_strcut(const char *s, size_t i);
size_t			pf_strlen(const char *s);
char			*pf_strsub(const char *s, unsigned int start, size_t len);
char			*pf_strjoin_len(const char *s1, const char *s2, int len);
char			*pf_strjoin_free_len(char *s1, char *s2, int len);
char			*pf_strnew(size_t size);

char			*pf_itoa(long long int n);
char			*pf_ftoa(long double n, int dec);
char			*pf_itoa_base_unsigned(uintmax_t n, int base, int maj);
int				pf_isdigit(int c);
int				pf_isinstr(char *str, char c);
char			*pf_strnjoin(char *s1, char *s2, int n);

void			*pf_memalloc(size_t size);
void			*pf_tabset(size_t len);

int				max(int a, int b);
int				min(int a, int b);

#endif
