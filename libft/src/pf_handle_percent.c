/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:19 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:19 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

t_printf	*pf_handle_percent(t_flags *spec, va_list args)
{
	char	*rst;
	int		len;
	int		i;

	(void)args;
	len = MAX(1, spec->width);
	rst = pf_memalloc(sizeof(*rst) * (len + 1));
	i = 0;
	if (spec->flags[minus])
		rst[i++] = '%';
	while (i < len - 1 + spec->flags[minus])
		rst[i++] = (spec->flags[zero] ? '0' : ' ');
	if (!spec->flags[minus])
		rst[i++] = '%';
	rst[i] = '\0';
	return (pf_lstnew(rst, pf_strlen(rst)));
}
