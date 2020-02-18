#include "../include/hello.h"

static size_t	ft_rest_begin_actualize(t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str1;
	char	*str;

	((t_philo*)(*philo)->data)->state = TO_REST;
	pthread_mutex_lock(&g_gmutex);
	ft_sprintf(&str1, "%s%s is resting\n", (*mother)->result, ((t_philo*)(*philo)->data)->name);
	free((*mother)->result);
(*mother)->result = str1;
	ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, REST, 0));
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "SE REPOSE", X_STATE,
			Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	return(time(NULL));
}

static void	ft_rest_mid_actualize(t_philo **data, t_philo_mother **mother, char *str[])
{
	char	*str1;
	ft_actualize((*data)->capsule, str[0], X_LIFE, Y_LIFE);
	ft_actualize((*data)->capsule, str[1], X_TIME, Y_TIME);
	if (!(*data)->life)
	{
		ft_sprintf(&str1, "%s%s est mort\n", (*mother)->result, (*data)->name);
		(*mother)->all_in_life = false;
		free((*mother)->result);
(*mother)->result = str1;
	}
}

int		ft_rest(t_philo_heart **philo, t_philo **data, t_philo_mother **mother)
{
	char			*str[2];
	size_t			begin_time;
	size_t			now_time;
	int				rest_t;

	rest_t = ft_handle_define(GET_INFOS, REST, 0);
	begin_time = ft_rest_begin_actualize(philo, mother);
	now_time = begin_time;
	while (now_time <= begin_time + rest_t && (*mother)->all_in_life)
	{
		usleep(SEC);
		(*data)->life = (*data)->life - 1;
		ft_sprintf(&str[0], "%d", (*data)->life);
		time((time_t*)&now_time);
		ft_sprintf(&str[1], "%zi", (int)((rest_t + begin_time) - now_time) > 0 ?
				(rest_t + begin_time) - now_time : 0);
	pthread_mutex_lock(&g_gmutex);
	ft_rest_mid_actualize(data, mother, str);
	if (now_time > begin_time + rest_t && (*mother)->all_in_life)
		ft_reserve_meal(philo);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str[0]);
	ft_strdel(&str[1]);
	}
	return (0);
}

e_ret_status	ft_can_you_do_eat(t_wand *left, t_wand *right, t_philo *data)
{
	int		ret_left;
	int		ret_right;

	(void)data;// A DEL
	ret_left = 0;
	ret_right = 0;
	if (left->reserve == FREE || left->reserve == EAT_RIGHT)
	{
		ret_left = pthread_mutex_trylock(&left->mutex);
		left->reserve = FREE;
	}
	if (right->reserve == FREE || right->reserve == EAT_LEFT)
	{
		ret_right = pthread_mutex_trylock(&right->mutex);
		right->reserve = FREE;
	}
	if (!ret_left && ret_right)
		return (LEFT);
	else if (ret_left && !ret_right)
		return (RIGHT);
	else if (ret_left && ret_right)
		return (NOTHING);
	else
		return (ALL);
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
