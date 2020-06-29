/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:18 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	if (!s)
		return (NULL);
	start--;
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (s[++start] && ++i < (int)len)
		str[i] = s[start];
	return (str);
}
