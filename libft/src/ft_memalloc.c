/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:15 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void		*ft_memalloc(size_t size)
{
	void	*s;

	if (!(s = (void *)malloc(sizeof(void) * size)))
		return (NULL);
	ft_bzero(s, size);
	return (s);
}
