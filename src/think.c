/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 11:31:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static size_t	ft_think_begin_actualize(t_philo_heart **philo, int wand)
{
	if (wand == LEFT)
	{
		if (((t_wand*)(*philo)->prev->data)->wand_state == FREE)
			((t_wand*)(*philo)->prev->data)->wand_state = THINK_RIGHT;
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	}
	else
	{
		if (((t_wand*)(*philo)->next->data)->wand_state == FREE)
			((t_wand*)(*philo)->next->data)->wand_state = THINK_LEFT;
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	}
	return (time(NULL));
}

int				ft_think(int ret, t_philo_heart **philo, t_philo **data,
														t_philo_mother **mother)
{
	size_t		begin_time;
	size_t		now_time;
	int			think_t;

	(*data)->state = TO_THINK;
	think_t = ft_handle_define(GET_INFOS, THINK, 0);
	begin_time = ft_think_begin_actualize(philo, ret);
	now_time = begin_time;
	while (now_time < begin_time + think_t && (*mother)->all_in_life)
	{
		usleep(SEC);
		(*data)->life--;
		time((time_t*)&now_time);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			(*mother)->all_in_life = false;
	}
	if (ret == LEFT &&
			((t_wand*)(*philo)->prev->data)->wand_state == THINK_LEFT)
		((t_wand*)(*philo)->prev->data)->wand_state = FREE;
	else if (ret == RIGHT &&
			((t_wand*)(*philo)->next->data)->wand_state == THINK_RIGHT)
		((t_wand*)(*philo)->next->data)->wand_state = FREE;
	return (0);
}
