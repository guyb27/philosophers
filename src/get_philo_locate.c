/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_locate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 06:00:54 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

t_philo_location	*ft_get_philo_locate(int wand_number, int x, int y)
{
	t_philo_location *locate;

	(void)y;
	locate = ft_memalloc(sizeof(t_philo_location));
	if (wand_number == 0)
		locate->x_capsule = 2;
	else if (wand_number == 6 || wand_number == 1)
		locate->x_capsule = 9;
	else if (wand_number == 5 || wand_number == 2)
		locate->x_capsule = 16;
	else if (wand_number == 4 || wand_number == 3)
		locate->x_capsule = 23;
	if (wand_number == 0)
		locate->y_capsule = (int)(x * 0.5) - 10;
	else if (wand_number == 6 || wand_number == 5)
		locate->y_capsule = (int)(x * 0.25) - 10;
	else if (wand_number == 1 || wand_number == 2)
		locate->y_capsule = (int)(x * 0.75) - 10;
	else if (wand_number == 4)
		locate->y_capsule = (int)(x * 0.30) - 10;
	else if (wand_number == 3)
		locate->y_capsule = (int)(x * 0.70) - 10;
	locate->init = false;
	return (locate);
}
