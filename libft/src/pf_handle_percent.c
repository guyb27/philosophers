/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_percent.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 03:14:19 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 14:05:43 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
