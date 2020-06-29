/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:50 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 05:01:02 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

void				ft_create_philo(t_philo_heart **philo_heart,
															t_screen_size ss)
{
	t_philo_heart	*new_philo_heart;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	new_philo_heart->type = PHILO;
	new_philo_heart->data = ft_memalloc(sizeof(t_philo));
	while (1)
	{
		if ((*philo_heart)->type == WAND &&
				(*philo_heart)->prev->type == WAND)
		{
			if (g_gmode == ALL_WINDOWS)
				((t_philo*)new_philo_heart->data)->locate =
					ft_get_philo_locate(
			((t_wand*)(*philo_heart)->prev->data)->locate->number, ss.x, ss.y);
			else
				((t_philo*)new_philo_heart->data)->locate = NULL;
			new_philo_heart->next = *philo_heart;
			new_philo_heart->prev = (*philo_heart)->prev;
			(*philo_heart)->prev->next = new_philo_heart;
			(*philo_heart)->prev = new_philo_heart;
			break ;
		}
		*philo_heart = (*philo_heart)->next;
	}
}

void				ft_create_wand(t_philo_heart **philo_heart,
															t_screen_size ss)
{
	t_wand			*wand;
	t_philo_heart	*new_philo_heart;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	new_philo_heart->type = WAND;
	wand = ft_memalloc(sizeof(t_wand));
	wand->wand_state = FREE;
	wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ft_handle_wand_location(&wand->locate, GET_INFOS, ss);
	new_philo_heart->data = wand;
	if (!*philo_heart)
	{
		*philo_heart = new_philo_heart;
		new_philo_heart->prev = new_philo_heart;
		new_philo_heart->next = new_philo_heart;
	}
	else
	{
		new_philo_heart->next = *philo_heart;
		new_philo_heart->prev = (*philo_heart)->prev;
		(*philo_heart)->prev->next = new_philo_heart;
		(*philo_heart)->prev = new_philo_heart;
		*philo_heart = (*philo_heart)->prev;
	}
}