/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:50:01 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static void	ft_init_and_print_wand(t_philo_heart *philo_heart)
{
	t_wand	*wand;

	wand = philo_heart->data;
	wand->locate->y_before =
		ft_strlen(((t_philo*)philo_heart->prev->data)->name) + 2;
	wand->locate->y_mid = wand->locate->y_before + 9;
	wand->locate->y_after = wand->locate->y_mid + 6 +
		ft_strlen(((t_philo*)philo_heart->next->data)->name);
	wand->locate->init = true;
}

int			ft_print_wand(t_philo_heart *philo_heart, t_philo_mother *mother,
																bool mutex_lock)
{
	if (((t_philo*)philo_heart->prev->data)->name &&
			((t_philo*)philo_heart->next->data)->name && g_gmode == ALL_WINDOWS)
	{
		mutex_lock ? pthread_mutex_lock(&g_gmutex) : 0;
		((t_wand*)philo_heart->data)->capsule = subwin(mother->win, 1, 40,
			((t_wand*)philo_heart->data)->locate->x_window,
			((t_wand*)philo_heart->data)->locate->y_window);
		ft_init_and_print_wand(philo_heart);
		mutex_lock ? pthread_mutex_unlock(&g_gmutex) : 0;
		return (1);
	}
	return (0);
}