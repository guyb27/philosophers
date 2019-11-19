/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_int.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 08:26:31 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:30:43 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int				pf_mallsize(intmax_t arg, t_flags *spec, char *tmp)
{
	int					len;

	if (arg == 0)
		spec->flags[hash] = 0;
	len = MAX((int)pf_strlen(tmp) + spec->flags[hash],
			(MAX(spec->width, spec->prec)));
	return (len);
}

static int				pf_is_space(t_flags *spec, char *tmp, intmax_t len, int i)
{
	if (!spec->flags[zero])
		return (i < len - (MAX((int)pf_strlen(tmp),
						spec->prec - spec->flags[hash]) + spec->flags[hash]));
	else
	{
		if (spec->prec == -1)
			return (0);
		else
		{
			if (spec->prec < spec->width)
				return (i < spec->width - MAX(spec->prec, (int)pf_strlen(tmp))
						- spec->flags[hash]);
			else
				return (0);
		}
	}
}

static int				pf_is_zero(t_flags *spec, char *tmp, intmax_t len, int *i)
{
	if (spec->flags[minus] && (int)pf_strlen(tmp) < spec->prec)
	{
		if (spec->prec > -1)
			return (i[0] < spec->prec - (int)pf_strlen(tmp));
		else
			return (i[0] < spec->flags[hash]);
	}
	else
		return (i[0] < len - ((int)pf_strlen(tmp) - i[1]));
}

static intmax_t			pf_get_arg(t_flags *spec, va_list args)
{
	intmax_t			arg;

	arg = va_arg(args, intmax_t);
	if (spec->size == hh && spec->conv == 'o')
		arg = (unsigned char)arg;
	else if (spec->size == h && spec->conv == 'o')
		arg = (unsigned short int)arg;
	else if (spec->size == l || spec->conv == 'O')
		arg = (unsigned long int)arg;
	else if (spec->size == ll)
		arg = (unsigned long long int)arg;
	else if (spec->size == j)
		arg = (intmax_t)arg;
	else if (spec->size == z)
		arg = (size_t)arg;
	else
		arg = (unsigned int)arg;
	return (arg);
}

t_printf				*pf_handle_oct(t_flags *spec, va_list args)
{
	char				*rst;
	char				*tmp;
	intmax_t			arg;
	int					len;
	int					i[2];

	arg = pf_get_arg(spec, args);
	if (spec->prec == 0 && arg == 0)
		return (pf_zeroprec(spec));
	tmp = pf_itoa_base_unsigned(arg, 8, 0);
	len = pf_mallsize(arg, spec, tmp);
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
