/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_tests.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 17:49:47 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 16:03:53 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
