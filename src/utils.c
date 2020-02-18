#include "../include/hello.h"

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	if (g_gmode == ALL_WINDOWS)
	{
		wmove(capsule, x, y);
		wclrtoeol(capsule);
		wprintw(capsule, data);
		wrefresh(capsule);
	}
}

bool		ft_is_most_hungry(t_philo_heart *heart)
{
	e_ret_status	ret;
	e_ret_status	disable_wand;
	size_t			life;

	ret = NOTHING;
	disable_wand = NOTHING;
	life = ((t_philo*)heart->data)->life;
	if (((t_wand*)heart->next->data)->reserve == FREE)
		ret = LEFT;
	else if (((t_philo*)heart->next->next->data)->life > life)
	{
		ret = LEFT;
		disable_wand = LEFT;
	}
	if (((t_wand*)heart->prev->data)->reserve == FREE)
		ret += RIGHT;
	else if (((t_philo*)heart->prev->prev->data)->life > life)
	{
		ret += RIGHT;
		disable_wand += RIGHT;
	}
	if (ret == ALL && (disable_wand == LEFT || disable_wand == ALL))
		((t_wand*)heart->prev->prev->prev->data)->reserve = FREE;
	if (ret == ALL && (disable_wand == RIGHT || disable_wand == ALL))
		((t_wand*)heart->next->next->next->data)->reserve = FREE;
	return (ret == ALL ? true : false);
}

void		ft_reserve_meal(t_philo_heart **heart)
{
	int		left;
	int		right;

	left = pthread_mutex_trylock(&((t_wand*)(*heart)->prev->data)->mutex);
	right = pthread_mutex_trylock(&((t_wand*)(*heart)->next->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*heart)->prev->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*heart)->next->data)->mutex);
	if (left && right && ((t_wand*)(*heart)->next->data)->reserve == FREE &&
	((t_wand*)(*heart)->prev->data)->reserve == FREE)
	{
		((t_wand*)(*heart)->prev->data)->reserve = EAT_RIGHT;
		((t_wand*)(*heart)->next->data)->reserve = EAT_LEFT;
	}
	else if (left && right && ft_is_most_hungry(*heart))
	{
		((t_wand*)(*heart)->prev->data)->reserve = EAT_RIGHT;
		((t_wand*)(*heart)->next->data)->reserve = EAT_LEFT;
	}
}
