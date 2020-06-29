/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strchr(const char *s, int c)
{
	size_t			i;

	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char*)&s[i]);
	else
		return (NULL);
}
