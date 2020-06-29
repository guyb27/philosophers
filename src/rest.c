/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:48:55 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

enum e_ret_status	ft_can_you_do_eat(t_wand *left, t_wand *right,
																t_philo *data)
{
	int				ret_left;
	int				ret_right;

	(void)data;
	ret_left = pthread_mutex_trylock(&left->mutex);
	ret_right = pthread_mutex_trylock(&right->mutex);
	if (!ret_left && ret_right)
		return (LEFT);
	else if (ret_left && !ret_right)
		return (RIGHT);
	else if (ret_left && ret_right)
		return (NOTHING);
	else
		return (ALL);
}

int					ft_rest(t_philo_heart **philo, t_philo **data,
														t_philo_mother **mother)
{
	size_t			begin_time;
	size_t			now_time;
	int				rest_t;

	rest_t = ft_handle_define(GET_INFOS, REST, 0);
	((t_philo*)(*philo)->data)->state = TO_REST;
	begin_time = time(NULL);
	now_time = begin_time;
	while (now_time < begin_time + rest_t && (*mother)->all_in_life)
	{
		usleep(SEC);
		(*data)->life = (*data)->life - 1;
		time((time_t*)&now_time);
		if (!(*data)->life)
			(*mother)->all_in_life = false;
	}
	return (0);
}

int					ft_eat_or_think(t_philo_heart **philo, t_philo **data,
														t_philo_mother **mother)
{
	int				ret;

	if ((ret = ft_can_you_do_eat((*philo)->prev->data, (*philo)->next->data,
					(*philo)->data)) == ALL)
		ft_eat(data, philo, mother);
	else if (ret == LEFT || ret == RIGHT)
		ft_think(ret, philo, data, mother);
	else
		return (1);
	return (0);
}
