/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isblank.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:16 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_str_isblank(char *str)
{
	int		i;

	i = 0;
	if (str && str[i])
	{
		while (str[i])
		{
			if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
				return (0);
			i++;
		}
	}
	return (1);
}
