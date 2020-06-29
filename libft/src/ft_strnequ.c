/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:18 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strnequ(const char *s1, const char *s2, size_t n)
{
	int i;

	i = -1;
	if (s1 && s2)
		while (++i < (int)n)
			if (s1[i] != s2[i])
				return (0);
	return (1);
}
