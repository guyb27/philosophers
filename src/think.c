#include "../include/hello.h"

static size_t	ft_think_begin_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother)
{
	char	*str;
	char	*str1;

		pthread_mutex_lock(&g_gmutex);
	str1 = ft_strjoin_free((*mother)->result, ((t_philo*)(*philo)->data)->name);
	(*mother)->result = ft_strjoin_free(str1, " is thinking\n");
	if (wand == LEFT)
	{
		if (((t_wand*)(*philo)->prev->data)->state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, THINK_RIGHT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	}
	else
	{
		if (((t_wand*)(*philo)->next->data)->state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, THINK_LEFT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	}
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, THINK, 0));
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "REFLECHIS",
															X_STATE, Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	return (time(NULL));
}

static void	ft_think_end_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother)
{
	if (wand == LEFT &&
			((t_wand*)(*philo)->prev->data)->state == THINK_LEFT)
	{
		((t_wand*)(*philo)->prev->data)->state = FREE;
		if ((*mother)->all_in_life)
		{
			pthread_mutex_lock(&g_gmutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, FREE);
			pthread_mutex_unlock(&g_gmutex);
		}
	}
	else if (wand == RIGHT &&
			((t_wand*)(*philo)->next->data)->state == THINK_RIGHT)
	{
		((t_wand*)(*philo)->next->data)->state = FREE;
		if ((*mother)->all_in_life)
		{
			pthread_mutex_lock(&g_gmutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, FREE);
			pthread_mutex_unlock(&g_gmutex);
		}
	}
}

static void		ft_think_mid_actualize(t_philo **data, char *str[],
								t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str1;
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*data)->capsule, str[0], X_TIME, Y_TIME);
		ft_actualize((*data)->capsule, str[1], X_LIFE, Y_LIFE);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
		{
			ft_sprintf(&str1, "%s%s est mort\n", (*mother)->result,
																(*data)->name);
			free((*mother)->result);
(*mother)->result = str1;
			(*mother)->all_in_life = false;
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
		usleep(SEC);
		(*data)->life--;
		ft_sprintf(&str[0], "%zi", (int)((begin_time + think_t) - now_time) >
				0 ? (begin_time + think_t) - now_time : 0);
		ft_sprintf(&str[1], "%d", (*data)->life);
		ft_think_mid_actualize(data, str, philo, mother);
		time((time_t*)&now_time);
		if (now_time > begin_time + think_t && (*mother)->all_in_life)
			ft_reserve_meal(philo);
		pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
	}
	ft_think_end_actualize(philo, ret, mother);
	return (0);
}
