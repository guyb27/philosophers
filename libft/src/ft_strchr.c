/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:17 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:17 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		if (*s == (char)c)
			return ((char *)s);
		while (*s++)
			if (*s == (char)c)
				return ((char *)s);
	}
	return (NULL);
}
