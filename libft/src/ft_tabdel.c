/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:18 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_tabdel(char ***tab)
{
	int		i;

	i = -1;
	if (*tab)
	{
		while ((*tab)[++i])
			ft_strdel(&(*tab)[i]);
		free(*tab);
		*tab = NULL;
	}
	return (0);
}
