/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 06:53:41 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:13:46 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/handlers.h"

static t_handlers	pf_tabinit(char conv, t_printf *(*fct)(t_flags*, va_list))
{
	t_handlers		ptr;

	ptr.conv = conv;
	ptr.fct_handle = fct;
	return (ptr);
}

static t_printf			*pf_select_conv(t_flags *spec, va_list args)
{
	t_handlers		tab_handlers[15];
	int				i;

	tab_handlers[0] = pf_tabinit('%', &pf_handle_percent);
	tab_handlers[1] = pf_tabinit('c', &pf_handle_char);
	tab_handlers[2] = pf_tabinit('s', &pf_handle_str);
	tab_handlers[3] = pf_tabinit('d', &pf_handle_signed_int);
	tab_handlers[4] = pf_tabinit('D', &pf_handle_signed_int);
	tab_handlers[5] = pf_tabinit('i', &pf_handle_signed_int);
	tab_handlers[6] = pf_tabinit('u', &pf_handle_unsigned_int);
	tab_handlers[7] = pf_tabinit('U', &pf_handle_unsigned_int);
	tab_handlers[8] = pf_tabinit('o', &pf_handle_oct);
	tab_handlers[9] = pf_tabinit('O', &pf_handle_oct);
	tab_handlers[10] = pf_tabinit('x', &pf_handle_hex);
	tab_handlers[11] = pf_tabinit('X', &pf_handle_hex);
	tab_handlers[12] = pf_tabinit('p', &pf_handle_p);
	tab_handlers[13] = pf_tabinit('f', &pf_handle_float);
	tab_handlers[14] = pf_tabinit('F', &pf_handle_float);
	i = -1;
	while (++i < 15)
	{
		if (tab_handlers[i].conv == spec->conv)
			return (tab_handlers[i].fct_handle(spec, args));
	}
	return (NULL);
}

t_printf			*pf_handle(char **str, va_list args, int a)
{
	t_flags			*spec;
	int				i;
	t_printf		*curr_list;

	i = a;
	while ((*str)[i] && pf_is_valid((*str)[i]) && !pf_is_conv((*str)[i]))
		i++;
	if (!(*str)[i] || !pf_is_conv((*str)[i]))
	{
		*str = &(*str)[i];
		return (pf_lstnew(NULL, -1));
	}
	spec = pf_parse(&(*str)[a]);
	curr_list = pf_select_conv(spec, args);
	free(spec);
	if (a > 1)
	{
		curr_list->str = pf_strnjoin(pf_strcut(*str, a - 1), curr_list->str,
				curr_list->size);
		curr_list->size += a - 1;
	}
	*str = &(*str)[i + 1];
	return (curr_list);
}

void				pf_utils_norme(char **rst, int *i, char *tmp)
{
	(*rst)[i[0]] = '\0';
	free(i);
	free(tmp);
}
