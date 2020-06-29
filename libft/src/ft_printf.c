/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:16 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	pf_inner_printf(int (*f)(void**, t_printf*), void **fd,
		va_list args, const char *format)
{
	char		*str;
	int			i;
	t_printf	*list;
	int			ret;

	str = (char*)format;
	i = 0;
	list = NULL;
	while (str[i])
	{
		if (str[i] == '%')
		{
			pf_lstaddend(&list, pf_handle(&str, args, i + 1));
			i = -1;
		}
		i++;
	}
	if (i > 0)
		pf_lstaddend(&list, pf_lstnew(pf_strcut(str, i), i));
	ret = f(fd, list);
	free(list);
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	int			ret;
	va_list		args;
	void		*tmp;
	int			fd;

	fd = 1;
	tmp = &fd;
	if (!format || !*format)
		return (0);
	va_start(args, format);
	ret = pf_inner_printf(pf_lstprint, &tmp, args, format);
	va_end(args);
	return (ret);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	int			ret;
	va_list		args;
	void		*tmp;

	tmp = &fd;
	if (!format || !*format || fd < 0)
		return (0);
	va_start(args, format);
	ret = pf_inner_printf(pf_lstprint, &tmp, args, format);
	va_end(args);
	return (ret);
}

int			ft_sprintf(char **str, const char *format, ...)
{
	int			ret;
	va_list		args;
	void		*tmp;

	tmp = &str;
	if (!format || !*format)
		return (0);
	va_start(args, format);
	ret = pf_inner_printf(pf_lstsprint, &tmp, args, format);
	*str = tmp;
	va_end(args);
	return (ret);
}

int			ft_fprintf(char *str, const char *format, ...)
{
	int			ret;
	va_list		args;
	void		*tmp;

	tmp = str;
	if (!format || !*format)
		return (0);
	va_start(args, format);
	ret = pf_inner_printf(pf_lstfprint, &tmp, args, format);
	va_end(args);
	return (ret);
}
