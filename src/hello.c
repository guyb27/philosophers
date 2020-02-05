#include "../include/hello.h"

void ft_init_curses(void)
{
	pthread_mutex_lock(&g_mut);
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
	curs_set(0);
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr,TRUE);
	bkgd(COLOR_PAIR(1));
	refresh();
	pthread_mutex_unlock(&g_mut);
}

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	wmove(capsule, x, y);
	wclrtoeol(capsule);
	wprintw(capsule, data);
	wrefresh(capsule);
}

WINDOW	*ft_create_philo_window(t_philo *philo)
{
	WINDOW *capsule;

	pthread_mutex_lock(&g_mut);
	capsule = subwin(stdscr, 4, 20, philo->locate->x_capsule, philo->locate->y_capsule);
	wbkgd(capsule, COLOR_PAIR(3));
	wmove(capsule, 0, 0);
	wprintw(capsule, "NAME: ");
	wprintw(capsule, philo->name);
	wmove(capsule, 1, 0);
	wprintw(capsule, "LIFE POINTS: ");
	wprintw(capsule, ft_itoa(philo->life));
	wmove(capsule, 2, 0);
	wprintw(capsule, "STATE: ");
	wprintw(capsule, philo->state == TO_REST ? "SE REPOSE" : philo->state == TO_EAT ? "MANGE" : philo->state == TO_THINK ? "PENSE" : "UNKNOW");
	wmove(capsule, 3, 0);
	wprintw(capsule, "TIME: ");
	wprintw(capsule, ft_itoa(philo->time));
	wrefresh(capsule);
	pthread_mutex_unlock(&g_mut);
	return (capsule);
}

size_t	ft_eat_begin_actualize(t_philo_heart **philo)
{
	char	*str;
	size_t	now_time;

	str = NULL;
	//ft_sprintf(&str, "%zi", EAT_T);
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, EAT, 0));
	((t_philo*)(*philo)->data)->state = TO_EAT;
	pthread_mutex_lock(&g_mut);
	ft_actualize_wand((t_philo_heart**)&(*philo)->prev, EAT_RIGHT);
	ft_actualize_wand((t_philo_heart**)&(*philo)->next, EAT_LEFT);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "MANGE", X_STATE, Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_mut);
	ft_strdel(&str);
	time((time_t*)&now_time);
	return (now_time);
}

void	ft_eat_end_actualize(t_philo_heart **philo)
{
	char	*str;

	str = NULL;
	if (g_all_in_life)
	{
		ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, LIFE, 0));
		((t_philo*)(*philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);
		pthread_mutex_lock(&g_mut);
		ft_actualize_wand(&(*philo)->prev, FREE);
		ft_actualize_wand(&(*philo)->next, FREE);
		ft_actualize((((t_philo*)(*philo)->data)->capsule), str, X_LIFE, Y_LIFE);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str);
	}
	pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
}

size_t	ft_think_begin_actualize(t_philo_heart **philo, int wand)
{
	char	*str;

	str = NULL;
	if (wand == LEFT)
	{
		pthread_mutex_lock(&g_mut);
		if (((t_wand*)(*philo)->prev->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, THINK_RIGHT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	}
	else// if (wand == RIGHT)
	{
		pthread_mutex_lock(&g_mut);
		if (((t_wand*)(*philo)->next->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, THINK_LEFT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	}
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "REFLECHIS", X_STATE, Y_STATE);
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, THINK, 0));
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_mut);
	ft_strdel(&str);
	return (time(NULL));
}

void	ft_think_end_actualize(t_philo_heart **philo, int wand)
{
	if (wand == LEFT &&
					((t_wand*)(*philo)->prev->data)->wand_state == THINK_LEFT)
	{
		((t_wand*)(*philo)->prev->data)->wand_state = FREE;
		if (g_all_in_life)
		{
			pthread_mutex_lock(&g_mut);
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, FREE);
			pthread_mutex_unlock(&g_mut);
		}
	}
	else if (wand == RIGHT &&
					((t_wand*)(*philo)->next->data)->wand_state == THINK_RIGHT)
	{
		((t_wand*)(*philo)->next->data)->wand_state = FREE;
		if (g_all_in_life)
		{
			pthread_mutex_lock(&g_mut);
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, FREE);
			pthread_mutex_unlock(&g_mut);
		}
	}
}

size_t	ft_rest_begin_actualize(t_philo_heart **philo)
{
	char	*str;

	str = NULL;
	((t_philo*)(*philo)->data)->state = TO_REST;
	//ft_sprintf(&str, "%d", REST_T);
	ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, REST, 0));
	pthread_mutex_lock(&g_mut);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "SE REPOSE", X_STATE,
																	Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_mut);
	ft_strdel(&str);
	return(time(NULL));
}

void	ft_close_window(t_philo_heart *philo)
{
	if (philo->type == PHILO)
	{
		free(((t_philo*)philo->data)->capsule);
		touchwin(stdscr);
		refresh();
		ft_dprintf(2, "DEL_PHILO: [%s]\n", ((t_philo*)philo->data)->name);
		((t_philo*)philo->data)->capsule = NULL;
		free(((t_philo*)philo->data)->locate);
		((t_philo*)philo->data)->locate = NULL;
	}
	else
	{
		free(((t_wand*)philo->data)->capsule);
		touchwin(stdscr);
		refresh();
		ft_dprintf(2, "DEL_WAND: [%d]\n", ((t_wand*)philo->data)->locate->number);
		((t_wand*)philo->data)->capsule = NULL;
		free(((t_wand*)philo->data)->locate);
		((t_wand*)philo->data)->locate = NULL;
	}
}

void	ft_free_philo_heart(t_philo_heart **philo)
{
	int		i;
	t_philo_heart	*tmp;

	i = -1;
	while (++i < NB_PHILO * 2)
	{
		tmp = *philo;
		ft_close_window(*philo);
		if ((*philo)->type == PHILO)
			free(((t_philo*)(*philo)->data)->name);
		*philo = (*philo)->next;
		free(tmp);
	}
	//touchwin(stdscr);
	//refresh();
	//endwin();


}
/*
t_screen_size	*ft_get_screen_size(t_screen_size ss, e_handle_static_function hsf)
{
	static t_screen_size	*locale_ss = NULL;
	t_screen_size	tmp_ss;

	if (hsf == INIT)
	{
		locale_ss = ft_memalloc(sizeof(t_screen_size));
		getmaxyx(stdscr, locale_ss->y, locale_ss->x);
	}
	else if (hsf == ACTUALIZE && locale_ss)
	{
		getmaxyx(stdscr, tmp_ss.y, tmp_ss.x);
		if (tmp_ss.x != locale_ss->x || tmp_ss.y != locale_ss->y)
			;//CLEAN ET REAFFICHER TOUTE LA WINDOW STDSCR
	}
	else if (hsf != GET_INFOS)
		return (NULL);
	return (locale_ss);
}*/
