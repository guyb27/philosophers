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

static size_t		ft_rest_begin_actualize(t_philo_heart **philo,
														t_philo_mother **mother)
{
	char			*str1;
	char			*str;

	((t_philo*)(*philo)->data)->state = TO_REST;
	pthread_mutex_lock(&g_gmutex);
	ft_sprintf(&str1, "%s%s is resting\n", (*mother)->result,
											((t_philo*)(*philo)->data)->name);
	free((*mother)->result);
	(*mother)->result = str1;
	ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, REST, 0));
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "SE REPOSE", X_STATE,
			Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	return (time(NULL));
}

static void			ft_rest_mid_actualize(t_philo **data,
										t_philo_mother **mother, char *str[])
{
	char			*str1;

	pthread_mutex_lock(&g_gmutex);
	ft_actualize((*data)->capsule, str[0], X_LIFE, Y_LIFE);
	ft_actualize((*data)->capsule, str[1], X_TIME, Y_TIME);
	if (!(*data)->life)
	{
		ft_sprintf(&str1, "%s%s est mort\n", (*mother)->result, (*data)->name);
		(*mother)->all_in_life = false;
		free((*mother)->result);
		(*mother)->result = str1;
	}
	pthread_mutex_unlock(&g_gmutex);
}

int					ft_rest(t_philo_heart **philo, t_philo **data,
														t_philo_mother **mother)
{
	char			*str[2];
	size_t			begin_time;
	size_t			now_time;
	int				rest_t;

	rest_t = ft_handle_define(GET_INFOS, REST, 0);
	str[0] = NULL;
	str[1] = NULL;
	begin_time = ft_rest_begin_actualize(philo, mother);
	now_time = begin_time;
	while (now_time < begin_time + rest_t && (*mother)->all_in_life)
	{
		usleep(SEC);
		(*data)->life = (*data)->life - 1;
		ft_sprintf(&str[0], "%d", (*data)->life);
		time((time_t*)&now_time);
		ft_sprintf(&str[1], "%zi", (int)((rest_t + begin_time) - now_time) > 0 ?
				(rest_t + begin_time) - now_time : 0);
		ft_rest_mid_actualize(data, mother, str);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
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
