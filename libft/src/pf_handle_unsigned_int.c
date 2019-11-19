/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_int.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 08:26:31 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:32:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_printf.h"

t_printf			*pf_zeroprec(t_flags *spec)
{
	char			*rst;
	int				len;
	int				i;

	len = MAX(spec->width, ((pf_isinstr("dDi", spec->conv) &&
					(spec->flags[space] || spec->flags[plus])) ||
				(pf_isinstr("oO", spec->conv) && spec->flags[hash])));
	rst = pf_memalloc(sizeof(*rst) * (len + 1));
	i = 0;
	if (spec->flags[minus] &&
			((pf_isinstr("dDi", spec->conv) && spec->flags[plus]) ||
			(pf_isinstr("oO", spec->conv && spec->flags[hash]))))
		rst[i++] = (pf_isinstr("dDi", spec->conv) ? '+' : '0');
	while (i < len - (pf_isinstr("dDoOi", spec->conv) && ((spec->flags[plus])
					|| spec->flags[hash])) && !spec->flags[minus])
		rst[i++] = ' ';
	if (i == len - 1)
		rst[i++] = (pf_isinstr("dDi", spec->conv) ? '+' : '0');
	rst[i] = '\0';
	return (pf_lstnew(rst, len));
}

static int			pf_is_space(t_flags *spec, char *tmp, intmax_t len, int i)
{
	if (!spec->flags[zero])
		return (i < len - (MAX((int)pf_strlen(tmp),
						spec->prec) + 2 * spec->flags[hash]));
	else
	{
		if (spec->prec == -1)
			return (0);
		else
		{
			if (spec->prec < spec->width)
				return (i < spec->width - MAX(spec->prec, (int)pf_strlen(tmp))
						- 2 * spec->flags[hash]);
			else
				return (0);
		}
	}
}

static int			pf_is_zero(t_flags *spec, char *tmp, intmax_t len, int *i)
{
	if (spec->flags[minus] && (intmax_t)pf_strlen(tmp) < len)
	{
		if (spec->prec > -1)
			return (i[0] < spec->prec - (int)pf_strlen(tmp));
		else
			return (i[0] < spec->flags[hash]);
	}
	else
		return (i[0] < len - ((int)pf_strlen(tmp) - i[1]));
}

static uintmax_t	pf_get_arg(t_flags *spec, va_list args)
{
	uintmax_t		arg;

	arg = va_arg(args, uintmax_t);
	if (spec->conv == 'U')
		arg = (unsigned long)arg;
	else if (spec->size == hh)
		arg = (unsigned char)arg;
	else if (spec->size == h)
		arg = (unsigned short)arg;
	else if (spec->size == l)
		arg = (unsigned long)arg;
	else if (spec->size == ll)
		arg = (unsigned long long)arg;
	else if (spec->size == j)
		arg = (uintmax_t)arg;
	else if (spec->size == z)
		arg = (size_t)arg;
	else
		arg = (unsigned int)arg;
	return (arg);
}

t_printf			*pf_handle_unsigned_int(t_flags *spec, va_list args)
{
	char			*rst;
	char			*tmp;
	uintmax_t		arg;
	int				len;
	int				i[2];

	arg = pf_get_arg(spec, args);
	if (spec->prec == 0 && arg == 0)
		return (pf_zeroprec(spec));
	tmp = pf_itoa_base_unsigned((uintmax_t)arg, 10, 0);
	len = MAX((int)pf_strlen(tmp), (MAX(spec->width, spec->prec)));
	rst = pf_memalloc(sizeof(*rst) * (len + 1));
	i[0] = 0;
	i[1] = 0;
	while (pf_is_space(spec, tmp, len, i[0]) && !spec->flags[minus])
		rst[(i[0])++] = ' ';
	while (pf_is_zero(spec, tmp, len, i))
		rst[i[0]++] = '0';
	while (tmp[i[1]])
		rst[i[0]++] = tmp[i[1]++];
	while (i[0] < len && spec->flags[minus])
		rst[i[0]++] = ' ';
	rst[i[0]] = '\0';
	free(tmp);
	return (pf_lstnew(rst, len));
}
