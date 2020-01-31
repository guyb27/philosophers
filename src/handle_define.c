#include "../include/hello.h"

static int		ft_handle_def_others(e_handle_static_function h,
													e_define_type d, int value)
{
	static int	nb_philo = NB_PHILO;
	static int	max_life = MAX_LIFE;

	if (h == ACTUALIZE && value >= 0)
	{
		if (d == NBPHILO)
			nb_philo = value;
		else if (d == LIFE)
			max_life = value;
		else
			return (1);
		return (0);
	}
	if (h == GET_INFOS && (d == NBPHILO || d == MAX_LIFE))
		return (d == NBPHILO ? nb_philo : max_life);
	return (1);
}

static int		ft_handle_def_time(e_handle_static_function h, e_define_type d,
																	int value)
{
	static int	eat_t = EAT_T;
	static int	think_t = THINK_T;
	static int	rest_t = REST_T;
	static int	timeout = TIMEOUT;

	if (h == ACTUALIZE && value >= 0)
	{
		if (d == EAT)
			eat_t = value;
		else if (d == REST)
			rest_t = value;
		else if (d == THINK)
			think_t = value;
		else if (d == TIME)
			timeout = value;
		else
			return (1);
		return (0);
	}
	if (h == GET_INFOS && (d == EAT || d == REST))
		return (d == EAT ? eat_t : rest_t);
	else if (h == GET_INFOS && (d == THINK || d == TIME))
		return (d == THINK ? think_t : timeout);
	return (1);
}

int		ft_handle_define(e_handle_static_function h, e_define_type d, int value)
{
	if (d == NBPHILO || d == MAX_LIFE)
		return (ft_handle_def_others(h, d, value));
	else
		return (ft_handle_define(h, d, value));
}
