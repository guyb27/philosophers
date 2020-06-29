/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:21 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:21 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char*)malloc(sizeof(*str) * (pf_strlen(s1) + 1));
	if (str == NULL)
		return (NULL);
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (i < pf_strlen(s1) + 1)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
