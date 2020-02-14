#include "../include/hello.h"

static size_t	ft_think_begin_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother)
{
	char	*str;

	str = (*mother)->result;
	ft_sprintf(&(*mother)->result, "%s%s pense\n", str, ((t_philo*)(*philo)->data)->name);
	//ft_strdel(&str);
	if (wand == LEFT)
	{
	pthread_mutex_lock(&g_gmutex);
		if (((t_wand*)(*philo)->prev->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, THINK_RIGHT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	}
	else// if (wand == RIGHT)
	{
	pthread_mutex_lock(&g_gmutex);
		if (((t_wand*)(*philo)->next->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, THINK_LEFT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	}
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, THINK, 0));
	//pthread_mutex_lock(&g_gmutex);//Je ne sais plus pk mais quand je met ca ca deconne
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "REFLECHIS", X_STATE, Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	return (time(NULL));
}

static void	ft_think_end_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother)
{
	if (wand == LEFT &&
					((t_wand*)(*philo)->prev->data)->wand_state == THINK_LEFT)
	{
		((t_wand*)(*philo)->prev->data)->wand_state = FREE;
		if ((*mother)->all_in_life)
		{
			pthread_mutex_lock(&g_gmutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, FREE);
			pthread_mutex_unlock(&g_gmutex);
		}
	}
	else if (wand == RIGHT &&
					((t_wand*)(*philo)->next->data)->wand_state == THINK_RIGHT)
	{
		((t_wand*)(*philo)->next->data)->wand_state = FREE;
		if ((*mother)->all_in_life)
		{
	pthread_mutex_lock(&g_gmutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, FREE);
	pthread_mutex_unlock(&g_gmutex);
		}
	}
}

int		ft_think(int ret, t_philo_heart **philo, t_philo **data, t_philo_mother **mother)
{
	size_t			begin_time;
	size_t			now_time;
	char			*str[2];
	int				think_t;

	think_t = ft_handle_define(GET_INFOS, THINK, 0);
	begin_time = ft_think_begin_actualize(philo, ret, mother);
	now_time = begin_time;
	while (now_time <= begin_time + think_t && (*mother)->all_in_life)
	{
		if (think_t > 0)
		{
			usleep(SEC);
			(*data)->life--;
		}
		time((time_t*)&now_time);
		ft_sprintf(&str[0], "%zi", (int)((begin_time + think_t) - now_time) >
				0 ? (begin_time + think_t) - now_time : 0);
		ft_sprintf(&str[1], "%d", (*data)->life);
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*data)->capsule, str[0], X_TIME, Y_TIME);
		ft_actualize((*data)->capsule, str[1], X_LIFE, Y_LIFE);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
		{
			ft_sprintf(&(*mother)->result, "%s%s est mort\n", (*mother)->result, (*data)->name);
			(*mother)->all_in_life = false;
		}
		pthread_mutex_unlock(&g_gmutex);
	}
	ft_think_end_actualize(philo, ret, mother);
	return (0);
}
