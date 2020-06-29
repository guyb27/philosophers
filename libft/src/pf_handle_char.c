/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:19 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:19 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

t_printf	*pf_handle_char(t_flags *spec, va_list args)
{
	char	arg;
	char	*str;
	int		i;
	int		len;

	arg = va_arg(args, int);
	if (spec->size == l)
		return (pf_lstnew(NULL, 0));
	i = 0;
	len = (spec->width == -1 ? 1 : spec->width);
	str = (char*)pf_memalloc(sizeof(*str) * (len + 1));
	if (spec->flags[minus])
		str[i++] = arg;
	while (i < len - !spec->flags[minus])
		str[i++] = (spec->flags[zero] ? '0' : ' ');
	if (i != len)
		str[i++] = arg;
	str[i] = '\0';
	return (pf_lstnew(str, len));
}
