/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:19 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:19 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t		ft_wordlen(const char *s, char c, size_t i)
{
	size_t	count;

	count = 0;
	if (s)
	{
		while (s[i] != c && s[i] != '\0')
		{
			count++;
			i++;
		}
	}
	return (count);
}
