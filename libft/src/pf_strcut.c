/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:21 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:21 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strcut(const char *s, size_t i)
{
	size_t	j;
	char	*rst;

	if (i <= 0)
		return (NULL);
	if (i > pf_strlen(s))
		i = pf_strlen(s);
	rst = (char*)pf_memalloc(sizeof(*rst) * (i + 1));
	j = 0;
	while (j < i && s[j])
	{
		rst[j] = s[j];
		j++;
	}
	rst[j] = '\0';
	return (rst);
}
