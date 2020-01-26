#include "../include/hello.h"

#define ENTER 10
#define ESCAPE 27

void ft_init_curses(void)
{
	//	g_mut = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&g_mut);
	initscr();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_WHITE,COLOR_RED);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	curs_set(0);
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr,TRUE);
	bkgd(COLOR_PAIR(1));
	move(0, 0);
	printw("A problem has been detected and windows been shut down to prevent damage to your computer.");
	move(1, 0);
	printw("UNMOUNTABLE_BOOT_VOLUME :");
	move(2, 0);
	printw("*** STOP: 0X89F1080ED (0X345A3BC5, 0X62348EB3A, 0X0967EAC4F0)");
	refresh();
	pthread_mutex_unlock(&g_mut);
}

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	pthread_mutex_lock(&g_mut);
	wmove(capsule, x, y);
	wclrtoeol(capsule);
	wprintw(capsule, data);
	wrefresh(capsule);
	pthread_mutex_unlock(&g_mut);
}
WINDOW	*ft_create_philo_window(t_philo *philo)
{
	WINDOW *capsule;

	pthread_mutex_lock(&g_mut);
	capsule = subwin(stdscr, 4, 25, philo->locate->x_capsule, philo->locate->y_capsule);
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

void		ft_actualize_wand(t_philo_heart **heart, e_wand_state new_state)
{
	t_wand	*wand;
	int		y;

	if ((*heart)->type == WAND && (*heart)->prev->type == PHILO && (*heart)->prev->type == PHILO)
	{
		wand = ((t_wand*)(*heart)->data);
		pthread_mutex_lock(&g_mut);
		if (wand->wand_state == THINK_LEFT || wand->wand_state == EAT_LEFT)
			y = wand->locate->y_before;
		else
			y = wand->wand_state == FREE ? wand->locate->y_mid : wand->locate->y_after;
		wmove(wand->capsule, 0, y);
		wprintw(wand->capsule, " ");
		wrefresh(wand->capsule);
		sleep(1);
		wand->wand_state = new_state;
		if (wand->wand_state == THINK_LEFT || wand->wand_state == EAT_LEFT)
			y = wand->locate->y_before;
		else
			y = wand->wand_state == FREE ? wand->locate->y_mid : wand->locate->y_after;
		wmove(wand->capsule, 0, y);
		wprintw(wand->capsule, "|");
		wrefresh(wand->capsule);
		pthread_mutex_unlock(&g_mut);
	}
}

size_t	ft_eat_begin_actualize(t_philo_heart **philo)
{
	char	*str;
	size_t	now_time;

	str = NULL;
	((t_philo*)(*philo)->data)->state = TO_EAT;
	ft_actualize_wand((t_philo_heart**)&(*philo)->prev, EAT_RIGHT);
	ft_actualize_wand((t_philo_heart**)&(*philo)->next, EAT_LEFT);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "MANGE", X_STATE, Y_STATE);
	ft_sprintf(&str, "%zi", EAT_T);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	ft_strdel(&str);
	time((time_t*)&now_time);
	return (now_time);
}

void	ft_eat_end_actualize(t_philo_heart **philo)
{
	char	*str;

	str = NULL;
	((t_philo*)(*philo)->data)->life = MAX_LIFE;
	ft_actualize_wand(&(*philo)->prev, FREE);
	ft_actualize_wand(&(*philo)->next, FREE);
	ft_sprintf(&str, "%d", MAX_LIFE);
	ft_actualize((((t_philo*)(*philo)->data)->capsule), str, X_LIFE, Y_LIFE);
	ft_strdel(&str);
	pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
}

size_t	ft_think_begin_actualize(t_philo_heart **philo, int wand)
{
	char	*str;
	size_t	now_time;

	str = NULL;
	if (wand == LEFT)
	{
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
		ft_actualize_wand((t_philo_heart**)&(*philo)->prev, THINK_RIGHT);
	}
	else if (wand == RIGHT)
	{
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
		ft_actualize_wand((t_philo_heart**)&(*philo)->next, THINK_LEFT);
	}
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "REFLECHIS", X_STATE, Y_STATE);
	ft_sprintf(&str, "%zi", THINK_T);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	ft_strdel(&str);
	time((time_t*)&now_time);
	return (now_time);
}

void	ft_think_end_actualize(t_philo_heart **philo, int wand)
{
	//Remettre la baguette au milieu si ell n'a pas etait prise entre deux.
	if (wand == LEFT)
	{
	}
	else if (wand == RIGHT)
	{
	}
}

size_t	ft_rest_begin_actualize(t_philo_heart **philo)
{
	char	*str;
	size_t	now_time;

	str = NULL;
	now_time = 0;
	((t_philo*)(*philo)->data)->state = TO_REST;
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "SE REPOSE", X_STATE, Y_STATE);
	ft_sprintf(&str, "%d", REST_T);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	ft_strdel(&str);
	time((time_t*)&now_time);
	return (now_time);
}
void	ft_print_wand(t_philo_heart **philo_heart)//Faire une fonction plus propre qui utilise ft_actualize
{
	t_wand	*wand;
	char *str = NULL;

	if ((*philo_heart)->type == WAND && (*philo_heart)->prev->type == PHILO && (*philo_heart)->next->type == PHILO)
	{
		pthread_mutex_lock(&g_mut);
		wand = (*philo_heart)->data;
		wmove(wand->capsule, 0, 0);
		wclrtoeol(wand->capsule);
		ft_sprintf(&str, "%d%s:[%s], MID:[%s], %s:[%s]",
		wand->locate->number,
		((t_philo*)(*philo_heart)->prev->data)->name,
		wand->wand_state == THINK_LEFT || wand->wand_state == EAT_LEFT ? "|" : " ",
		wand->wand_state == FREE ? "|" : " ",
		((t_philo*)(*philo_heart)->next->data)->name,
		wand->wand_state == THINK_RIGHT || wand->wand_state == EAT_RIGHT ? "|" : " "
		);
		wand->locate->y_before = ft_strlen(((t_philo*)(*philo_heart)->prev->data)->name) + 3;
		wand->locate->y_mid = wand->locate->y_before + 9;
		wand->locate->y_after = wand->locate->y_mid + 6 + ft_strlen(((t_philo*)(*philo_heart)->next->data)->name);
		wprintw(wand->capsule, str);
		wrefresh(wand->capsule);
		ft_dprintf(2, "%d:[%s]\n",
		wand->locate->number,
		str
		);
		ft_dprintf(2, "%d:y_before(%d) = prev_philo_name(%d) + 3\n",
		wand->locate->number,
		wand->locate->y_before,
		ft_strlen(((t_philo*)(*philo_heart)->prev->data)->name)
		);
		ft_dprintf(2, "%d:y_mid(%d) = y_before(%d) + 9\n",
		wand->locate->number,
		wand->locate->y_mid,
		wand->locate->y_before
		);
		ft_dprintf(2, "%d:y_after(%d) = y_mid(%d) + 6 + next_philo_name()\n",
		wand->locate->number,
		wand->locate->y_after,
		wand->locate->y_mid,
		ft_strlen(((t_philo*)(*philo_heart)->next->data)->name)
		);
		ft_strdel(&str);
		pthread_mutex_unlock(&g_mut);
	}
}
