/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:17 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:17 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dest;

	i = -1;
	dest = NULL;
	if (!s1)
		return (NULL);
	if (!(dest = ft_strnew(ft_strlen(s1))))
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	return (dest);
}
