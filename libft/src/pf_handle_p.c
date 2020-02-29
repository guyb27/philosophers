/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:19 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 13:00:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static t_printf	*pf_arg_zero(t_flags *spec)
{
	char		*rst;
	int			len;
	int			i;

	if (spec->prec == -1)
		spec->prec = 1;
	len = max(spec->prec + 2, spec->width);
	rst = pf_memalloc(sizeof(*rst) * len);
	i = 0;
	if (!spec->flags[minus])
		while (i < len - 3)
			rst[i++] = ' ';
	rst[i++] = '0';
	rst[i++] = 'x';
	if (spec->prec != 0)
		rst[i++] = '0';
	while (i < len)
		rst[i++] = ' ';
	rst[i] = '\0';
	return (pf_lstnew(rst, pf_strlen(rst)));
}

t_printf		*pf_handle_p(t_flags *spec, va_list args)
{
	char		*rst;
	char		*tmp;
	void		*arg;
	int			*i;
	int			len;

	arg = va_arg(args, void*);
	if (arg == 0)
		return (pf_arg_zero(spec));
	tmp = pf_itoa_base_unsigned((long int)arg, 16, 0);
	if (spec->width == -1)
		spec->width = 0;
	len = max(spec->prec + 3, max((int)pf_strlen(tmp) + 3, spec->width + 1));
	rst = pf_memalloc(sizeof(*tmp) * len);
	i = pf_tabset(2);
	while (!spec->flags[minus] && spec->width > i[0] + (int)pf_strlen(tmp) + 2)
		rst[(i[0])++] = ' ';
	rst[(i[0])++] = '0';
	rst[(i[0])++] = 'x';
	while (tmp[i[1]])
		rst[(i[0])++] = tmp[i[1]++];
	while (i[0] < spec->width)
		rst[(i[0])++] = ' ';
	pf_utils_norme(&rst, i, tmp);
	return (pf_lstnew(rst, pf_strlen(rst)));
}
