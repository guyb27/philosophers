/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:18 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strreplace(char ***tablo, int index, char *by)
{
	if (*tablo && (*tablo)[index])
	{
		ft_strdel(&(*tablo)[index]);
		(*tablo)[index] = ft_strdup(by);
	}
	return (0);
}
