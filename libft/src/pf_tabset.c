/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_tabset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:21 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:21 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft_printf.h"

void	*pf_tabset(size_t len)
{
	int		*tab;

	tab = pf_memalloc(sizeof(*tab) * len);
	while (len > 0)
	{
		len--;
		tab[len] = 0;
	}
	return (tab);
}
