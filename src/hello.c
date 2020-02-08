#include "../include/hello.h"

void ft_init_curses(void)
{
	initscr();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_WHITE,COLOR_RED);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	init_pair(4,COLOR_BLUE,COLOR_WHITE);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_GREEN,COLOR_BLACK);
	init_pair(7,COLOR_BLACK,COLOR_GREEN);
	init_pair(8,COLOR_BLACK,COLOR_RED);
	init_pair(9, COLOR_CYAN,COLOR_MAGENTA);
	curs_set(0);
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr,FALSE);
	bkgd(COLOR_PAIR(1));
	refresh();
}

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	wmove(capsule, x, y);
	wclrtoeol(capsule);
	wprintw(capsule, data);
	wrefresh(capsule);
}

WINDOW	*ft_create_philo_window(t_philo *philo, t_philo_mother **mother)
{
	WINDOW *capsule;

	pthread_mutex_lock(&(*mother)->mutex);
	philo->locate->init = true;
	capsule = subwin((*mother)->win, 4, 20, philo->locate->x_capsule, philo->locate->y_capsule);
	wbkgd(capsule, COLOR_PAIR(3));
	wmove(capsule, 0, 0);
	wprintw(capsule, "NAME: ");
	wprintw(capsule, philo->name);
	wmove(capsule, 1, 0);
	wprintw(capsule, "LIFE POINTS: ");
	wprintw(capsule, "%d", philo->life);
	wmove(capsule, 2, 0);
	wprintw(capsule, "STATE: ");
	wprintw(capsule, philo->state == TO_REST ? "SE REPOSE" : philo->state == TO_EAT ? "MANGE" : philo->state == TO_THINK ? "PENSE" : "UNKNOW");
	wmove(capsule, 3, 0);
	wprintw(capsule, "TIME: ");
	wprintw(capsule, "%d", philo->time);
	wrefresh(capsule);
	pthread_mutex_unlock(&(*mother)->mutex);
	return (capsule);
}

size_t	ft_eat_begin_actualize(t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str;
	size_t	now_time;

	str = NULL;
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, EAT, 0));
	((t_philo*)(*philo)->data)->state = TO_EAT;
	pthread_mutex_lock(&(*mother)->mutex);
	ft_actualize_wand((t_philo_heart**)&(*philo)->prev, EAT_RIGHT);
	ft_actualize_wand((t_philo_heart**)&(*philo)->next, EAT_LEFT);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "MANGE", X_STATE, Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&(*mother)->mutex);
	ft_strdel(&str);
	time((time_t*)&now_time);
	return (now_time);
}

void	ft_eat_end_actualize(t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str;

	str = NULL;
	if ((*mother)->all_in_life)
	{
		ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, LIFE, 0));
		((t_philo*)(*philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);
	pthread_mutex_lock(&(*mother)->mutex);
		ft_actualize_wand(&(*philo)->prev, FREE);
		ft_actualize_wand(&(*philo)->next, FREE);
		ft_actualize((((t_philo*)(*philo)->data)->capsule), str, X_LIFE, Y_LIFE);
	pthread_mutex_unlock(&(*mother)->mutex);
		ft_strdel(&str);
	}
	pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
}

size_t	ft_think_begin_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother)
{
	char	*str;

	str = NULL;
	if (wand == LEFT)
	{
	pthread_mutex_lock(&(*mother)->mutex);
		if (((t_wand*)(*philo)->prev->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, THINK_RIGHT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	}
	else// if (wand == RIGHT)
	{
	pthread_mutex_lock(&(*mother)->mutex);
		if (((t_wand*)(*philo)->next->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, THINK_LEFT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	}
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "REFLECHIS", X_STATE, Y_STATE);
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, THINK, 0));
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&(*mother)->mutex);
	ft_strdel(&str);
	return (time(NULL));
}

void	ft_think_end_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother)
{
	if (wand == LEFT &&
					((t_wand*)(*philo)->prev->data)->wand_state == THINK_LEFT)
	{
		((t_wand*)(*philo)->prev->data)->wand_state = FREE;
		if ((*mother)->all_in_life)
		{
			pthread_mutex_lock(&(*mother)->mutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, FREE);
			pthread_mutex_unlock(&(*mother)->mutex);
		}
	}
	else if (wand == RIGHT &&
					((t_wand*)(*philo)->next->data)->wand_state == THINK_RIGHT)
	{
		((t_wand*)(*philo)->next->data)->wand_state = FREE;
		if ((*mother)->all_in_life)
		{
	pthread_mutex_lock(&(*mother)->mutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, FREE);
	pthread_mutex_unlock(&(*mother)->mutex);
		}
	}
}

size_t	ft_rest_begin_actualize(t_philo_heart **philo, t_philo_mother **mother)
{
	char	*str;

	str = NULL;
	((t_philo*)(*philo)->data)->state = TO_REST;
	ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, REST, 0));
	pthread_mutex_lock(&(*mother)->mutex);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "SE REPOSE", X_STATE,
																	Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&(*mother)->mutex);
	ft_strdel(&str);
	return(time(NULL));
}

void	ft_close_window(t_philo_heart *philo)
{
	if (philo->type == PHILO)
	{
		delwin(((t_philo*)philo->data)->capsule);
		free(((t_philo*)philo->data)->locate);
		free(((t_philo*)philo->data)->name);
		free((t_philo*)philo->data);
	}
	else
	{
		delwin(((t_wand*)philo->data)->capsule);
		free(((t_wand*)philo->data)->locate);
		free((t_wand*)philo->data);
	}
}

void	ft_free_philo_heart(t_philo_heart *philo)
{
	int		i;
	t_philo_heart	*tmp;

	i = -1;
	while (++i < ft_handle_define(GET_INFOS, NBPHILO, 0) * 2)
	{
		tmp = philo;
		ft_close_window(philo);
		philo = philo->next;
		free(tmp);
	}
}

void	ft_free_philo_mother(t_philo_mother *mother)
{
	ft_free_philo_heart(mother->heart);
	delwin(mother->win_game_var);
	delwin(mother->state_game);
	delwin(mother->win);
	touchwin(stdscr);
	free(mother);
	refresh();
}
