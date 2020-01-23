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
	char	*str;

	str = NULL;
	//(*wand)->wand_state = new_state;
	((t_wand*)(*heart)->data)->wand_state = new_state;
	ft_sprintf(&str, "%s:[ ], MID:[0], %s:[ ]",
	((t_philo*)(*heart)->prev->data)->name,
	((t_philo*)(*heart)->next->data)->name
	);
	//ft_actualize((*wand)->capsule, str, 0, 0);
	ft_actualize(((t_wand*)(*heart)->data)->capsule, str, 0, 0);
	ft_strdel(&str);
}

void	ft_print_wand(t_philo_heart *philo_heart)//Faire une fonction plus propre qui utilise ft_actualize
{
	t_wand	*wand;
	t_philo		*philo;

	if (philo_heart->type == WAND)
	{
		pthread_mutex_lock(&g_mut);
		wand = philo_heart->data;
		wmove(wand->capsule, 0, 0);
		wclrtoeol(wand->capsule);
		if (philo_heart->prev->type == PHILO)
		{
			philo = philo_heart->prev->data;
			wprintw(wand->capsule, philo->name);
			if (wand->wand_state == THINK_LEFT || wand->wand_state == EAT_LEFT)
				wprintw(wand->capsule, ":[|], ");
			else
				wprintw(wand->capsule, ":[ ], ");
		}
		if (wand->wand_state == FREE)
			wprintw(wand->capsule, "MID:[|]");
		else
			wprintw(wand->capsule, "MID:[ ]");
		if (philo_heart->next->type == PHILO)
		{
			wprintw(wand->capsule, ", ");
			philo = philo_heart->prev->data;
			wprintw(wand->capsule, philo->name);
			if (wand->wand_state == THINK_RIGHT || wand->wand_state == EAT_RIGHT)
				wprintw(wand->capsule, ":[|]");
			else
				wprintw(wand->capsule, ":[ ]");
		}
		wrefresh(wand->capsule);
		pthread_mutex_unlock(&g_mut);
	}
}
