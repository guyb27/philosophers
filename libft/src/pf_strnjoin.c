/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:21 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:21 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strnjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		i2;

	if (!s1)
		return (NULL);
	if (!s2)
	{
		str = pf_strdup(s1);
		return (str);
	}
	if (!(str = pf_memalloc(pf_strlen(s1) + n + 1)))
		return (NULL);
	i = -1;
	i2 = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (i2 < n)
		str[i++] = s2[i2++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
