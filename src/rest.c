#include "../include/hello.h"

e_ret_status	ft_can_you_do_eat(t_wand *left, t_wand *right, t_philo *data)
{
	int		ret_left;
	int		ret_right;

	(void)data;// A DEL
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

size_t	ft_rest_begin_actualize(t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str;

	str = (*mother)->result;
	ft_sprintf(&(*mother)->result, "%s%s se repose\n", str, ((t_philo*)(*philo)->data)->name);
	//ft_strdel(&str);
	((t_philo*)(*philo)->data)->state = TO_REST;
	ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, REST, 0));
	pthread_mutex_lock(&g_gmutex);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "SE REPOSE", X_STATE,
																	Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	return(time(NULL));
}
int		ft_rest(t_philo_heart **philo, t_philo **data, t_philo_mother **mother)
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
	while (now_time <= begin_time + rest_t && (*mother)->all_in_life)
	{
		if (rest_t > 0)
		{
			usleep(SEC);
			(*data)->life = (*data)->life - 1;
		}
		ft_sprintf(&str[0], "%d", (*data)->life);
		time((time_t*)&now_time);
		ft_sprintf(&str[1], "%zi", (int)((rest_t + begin_time) - now_time) > 0 ?
				(rest_t + begin_time) - now_time : 0);
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*data)->capsule, str[0], X_LIFE, Y_LIFE);
		ft_actualize((*data)->capsule, str[1], X_TIME, Y_TIME);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(*data)->life)
		{
			ft_sprintf(&(*mother)->result, "%s%s est mort\n", (*mother)->result, (*data)->name);
			(*mother)->all_in_life = false;
		}
		pthread_mutex_unlock(&g_gmutex);
	}
	return (0);
}

int		ft_eat_or_think(t_philo_heart **philo, t_philo **data, t_philo_mother **mother)
{
	int ret;

	if ((ret = ft_can_you_do_eat((*philo)->prev->data, (*philo)->next->data,
					(*philo)->data)) == ALL)
		ft_eat(data, philo, mother);
	else if (ret == LEFT || ret == RIGHT)
		ft_think(ret, philo, data, mother);
	else
		return (1);
	return (0);
}
