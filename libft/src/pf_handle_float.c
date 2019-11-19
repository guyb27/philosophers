/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_float.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 12:27:47 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:19:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int				pf_mallsize(t_flags *spec, long double i)
{
	int					rst;

	rst = 1;
	if (i < 0 || spec->flags[plus] || spec->flags[space])
		rst++;
	while (i <= -10 || i >= 10)
	{
		i /= 10;
		rst++;
	}
	if (spec->prec > 0)
		rst += spec->prec + 1;
	rst = MAX(rst, spec->width);
	return (rst);
}

static int				pf_is_space(t_flags *spec, char *tmp, intmax_t len, int i)
{
	if (spec->flags[minus])
		return (0);
	return (!spec->flags[zero] && i < len - (int)pf_strlen(tmp));
}

static int				pf_is_zero(t_flags *spec, char *tmp, intmax_t len, int i)
{
	if (spec->flags[minus])
		return (0);
	return (i < len - (int)pf_strlen(tmp));
}

static long double		pf_get_arg(t_flags *spec, va_list args)
{
	long double			arg;

	if (spec->flags[maj_l])
		arg = va_arg(args, long double);
	else
		arg = va_arg(args, double);
	if (spec->prec == -1)
		spec->prec = 6;
	return (arg);
}

t_printf				*pf_handle_float(t_flags *spec, va_list args)
{
	char				*rst;
	char				*tmp;
	long double			arg;
	int					len;
	int					*i;

	arg = pf_get_arg(spec, args);
	tmp = pf_ftoa(arg, spec->prec);
	len = pf_mallsize(spec, arg);
	rst = pf_memalloc(sizeof(*rst) * (len + 1));
	i = pf_tabset(2);
	while (pf_is_space(spec, tmp, len, i[0]))
		rst[(i[0])++] = ' ';
	if (tmp[i[1]] == '-' || spec->flags[plus])
		rst[i[0]++] = (tmp[i[1]] == '-' ? tmp[i[1]++] : '+');
	while (pf_is_zero(spec, tmp, len, i[0]))
		rst[i[0]++] = '0';
	while (tmp[i[1]])
		rst[i[0]++] = tmp[i[1]++];
	while (i[0] < len && spec->flags[minus])
		rst[i[0]++] = ' ';
	rst[i[0]] = '\0';
	free(tmp);
	return (pf_lstnew(rst, len));
}
