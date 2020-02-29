/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int		pf_is_conv(const char c)
{
	return (pf_strchr("%sdDioOuUxXcpfF", c) != NULL);
}

int		pf_is_size(const char c)
{
	return (pf_strchr("hljz", c) != NULL);
}

int		pf_is_flag(const char c)
{
	return (pf_strchr("0#-+ L", c) != NULL);
}

int		pf_is_valid(const char c)
{
	return (pf_is_conv(c) || pf_is_size(c) || pf_is_flag(c) || pf_isdigit(c)
			|| c == '.');
}
