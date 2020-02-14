#include "../include/hello.h"

static size_t	ft_eat_begin_actualize(t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str;
	size_t	now_time;

	str = (*mother)->result;
	ft_sprintf(&(*mother)->result, "%s%s mange\n", str, ((t_philo*)(*philo)->data)->name);
	//ft_strdel(&str);
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, EAT, 0));
	((t_philo*)(*philo)->data)->state = TO_EAT;
	pthread_mutex_lock(&g_gmutex);
	ft_actualize_wand((t_philo_heart**)&(*philo)->prev, EAT_RIGHT);
	ft_actualize_wand((t_philo_heart**)&(*philo)->next, EAT_LEFT);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "MANGE", X_STATE, Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	time((time_t*)&now_time);
	return (now_time);
}

static void	ft_eat_end_actualize(t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str;

	str = NULL;
	if ((*mother)->all_in_life)
	{
		ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, LIFE, 0));
		((t_philo*)(*philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);
	pthread_mutex_lock(&g_gmutex);
		ft_actualize_wand(&(*philo)->prev, FREE);
		ft_actualize_wand(&(*philo)->next, FREE);
		ft_actualize((((t_philo*)(*philo)->data)->capsule), str, X_LIFE, Y_LIFE);
	pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str);
	}
	pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
}

int		ft_eat(t_philo **data, t_philo_heart **philo, t_philo_mother **mother)
{
	char			*str;
	size_t			begin_time;
	size_t			now_time;
	int				eat_t;

	eat_t = ft_handle_define(GET_INFOS, EAT, 0);
	str = NULL;
	begin_time = ft_eat_begin_actualize(philo, mother);
	now_time = begin_time;

	while (now_time <= begin_time + eat_t && (*mother)->all_in_life)
	{
		if (eat_t > 0)
			usleep(SEC);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", (int)((begin_time + eat_t) - now_time) > 0 ?
				(begin_time + eat_t) - now_time : 0);
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
		ft_strdel(&str);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
		{
			ft_sprintf(&(*mother)->result, "%s%s est mort\n", (*mother)->result, (*data)->name);
			(*mother)->all_in_life = false;
		}
		pthread_mutex_unlock(&g_gmutex);
	}
	ft_eat_end_actualize(philo, mother);
	return (0);
}