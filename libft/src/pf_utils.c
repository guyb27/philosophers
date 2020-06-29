/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:51:26 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 13:21:41 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft_printf.h"

void	pf_bzero(void *s, size_t n)
{
	while (n)
	{
		((int*)s)[n] = 0;
		n--;
	}
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}

int		min(int a, int b)
{
	return (a > b ? b : a);
}
