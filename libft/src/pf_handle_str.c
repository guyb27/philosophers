/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_str.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 04:06:07 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:31:22 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/handlers.h"

static int	pf_mallsize(t_flags *spec, char *arg)
{
	int		tmp;

	if (spec->prec == -1 || spec->prec > (int)pf_strlen(arg))
		spec->prec = pf_strlen(arg);
	tmp = MIN(spec->prec, (int)pf_strlen(arg));
	return (MAX(tmp, spec->width));
}

t_printf	*pf_handle_str(t_flags *spec, va_list args)
{
	char	*arg;
	char	*rst;
	int		i[2];
	int		len;

	if ((arg = va_arg(args, char*)) == NULL)
		arg = "(null)";
	if (spec->size == l)
		return (pf_lstnew(NULL, 0));
	len = pf_mallsize(spec, arg);
	if ((rst = (char*)pf_memalloc(sizeof(*rst) * (len + 1))) == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (i[0] < (len - spec->prec) && !spec->flags[minus])
		rst[i[0]++] = (spec->flags[zero] ? '0' : ' ');
	while (i[0] < (spec->flags[minus] ? spec->prec : len))
		rst[i[0]++] = arg[i[1]++];
	while (i[0] < len)
		rst[i[0]++] = ' ';
	rst[i[0]] = '\0';
	return (pf_lstnew(rst, len));
}
