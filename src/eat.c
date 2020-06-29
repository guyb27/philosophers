/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:50 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 05:05:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static size_t	ft_eat_begin_actualize(t_philo_heart **philo)
{
	size_t		now_time;

	((t_philo*)(*philo)->data)->state = TO_EAT;
	pthread_mutex_lock(&g_gmutex);
	((t_wand*)(*philo)->prev->data)->wand_state = EAT_RIGHT;
	((t_wand*)(*philo)->next->data)->wand_state = EAT_LEFT;
	pthread_mutex_unlock(&g_gmutex);
	time((time_t*)&now_time);
	return (now_time);
}

static void		ft_eat_end_actualize(t_philo_heart **philo,
														t_philo_mother **mother)
{
	char		*str;

	str = NULL;
	if ((*mother)->all_in_life)
	{
		ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, LIFE, 0));
		((t_philo*)(*philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);

		((t_wand*)(*philo)->prev->data)->wand_state = FREE;
		((t_wand*)(*philo)->next->data)->wand_state = FREE;
		ft_strdel(&str);
	}
	pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
}

int				ft_eat(t_philo **data, t_philo_heart **philo,
														t_philo_mother **mother)
{
	size_t		begin_time;
	size_t		now_time;
	int			eat_t;
(void)data;
	eat_t = ft_handle_define(GET_INFOS, EAT, 0);
	begin_time = ft_eat_begin_actualize(philo);
	now_time = begin_time;
	while (now_time < begin_time + eat_t && (*mother)->all_in_life)
	{
		usleep(SEC);
		time((time_t*)&now_time);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			(*mother)->all_in_life = false;
	}
	ft_eat_end_actualize(philo, mother);
	return (0);
}
