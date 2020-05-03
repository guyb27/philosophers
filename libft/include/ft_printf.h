/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:48:11 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 13:27:07 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "parse.h"
# include "libft_printf.h"
# include "lists.h"
# include "handlers.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>


int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_sprintf(char **str, const char *format, ...);
int				ft_fprintf(char *str, const char *format, ...);

#endif
