#include "../include/hello.h"

void	ft_a_philo_is_dead(void)//AFFICHER 'A PHILOPHER IS DEAD' EN DESSOUS D UNE COULEUR VOYANTE
{
	int			key, x, y;
	WINDOW		*end_window;

	key = 0;
	getmaxyx(stdscr, y, x);
	end_window = subwin(stdscr, 1, y - 1, 0, x - 1);
	wbkgd(end_window, COLOR_PAIR(5));
	wmove(end_window, 0, 0);
	wprintw(end_window, "A PHILO IS DEAD !!!");
	wrefresh(end_window);
	while (key != 27)
	{
		key = getch();
	}
	delwin(end_window);
}

void	ft_end_game(char *str)//AFFICHER 'NOW IT S TIME TO DANCE' EN DESSOUS D UNE COULEUR VOYANTE
{
	int			i;
	int			x, y;
	int			key;
	WINDOW		*end_window;

	getmaxyx(stdscr, y, x);
	end_window = subwin(stdscr, 1, x, y - 1, 0);
	wbkgd(end_window, COLOR_PAIR(g_all_in_life ? 6 : 5));
	wmove(end_window, 0, (x / 2) - (ft_strlen(str) / 2));
	wprintw(end_window, str);
	wrefresh(end_window);
	key = 0;
	g_all_in_life = false;
	while (key != 27)
		key = getch();
	delwin(end_window);
}

WINDOW	*ft_print_game_var(void)
{
	WINDOW			*base;
	int				x, y;

	getmaxyx(stdscr, y, x);
	pthread_mutex_lock(&g_mut);
	base = subwin(stdscr, 5, 25, 1, x - 26);
	wbkgd(base, COLOR_PAIR(2));
	wmove(base, 0, 0);
	wprintw(base, "MAX_LIFE: ");
	//wprintw(base, ft_itoa(MAX_LIFE));
	wprintw(base, ft_itoa(ft_handle_define(GET_INFOS, LIFE, 0)));
	wmove(base, 1, 0);
	wprintw(base, "EAT_TIME: ");
	//wprintw(base, ft_itoa(EAT_T));
	wprintw(base, ft_itoa(ft_handle_define(GET_INFOS, EAT, 0)));
	wmove(base, 2, 0);
	wprintw(base, "REST_TIME: ");
	wprintw(base, ft_itoa(ft_handle_define(GET_INFOS, REST, 0)));
	//wprintw(base, ft_itoa(REST_T));
	wmove(base, 3, 0);
	wprintw(base, "THINK_TIME: ");
	wprintw(base, ft_itoa(ft_handle_define(GET_INFOS, THINK, 0)));
	//wprintw(base, ft_itoa(THINK_T));
	wmove(base, 4, 0);
	wprintw(base, "TIME LEFT: ");
	//wprintw(base, ft_itoa(TIMEOUT));
	wprintw(base, ft_itoa(ft_handle_define(GET_INFOS, TIME, 0)));
	wrefresh(base);
	pthread_mutex_unlock(&g_mut);
	return (base);
}

void	ft_main_loop(void)
{
	size_t			begin_time;
	size_t			now_time;
	char			*str;
	WINDOW			*base;
	int				timeout;

	timeout = ft_handle_define(GET_INFOS, TIME, 0);
	str = NULL;
	base = ft_print_game_var();
	time( (time_t*)&begin_time );
	now_time = begin_time;
	//while (now_time < begin_time + TIMEOUT && g_all_in_life)
	while (now_time < begin_time + timeout && g_all_in_life)
	{
		usleep(SEC);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", timeout - (now_time - begin_time));
		//ft_sprintf(&str, "%zi", TIMEOUT - (now_time - begin_time));
		pthread_mutex_lock(&g_mut);
		ft_actualize(base, str, X_TIMEOUT, Y_TIMEOUT);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str);
	}
	usleep(SEC / 2);
	ft_end_game(g_all_in_life ? "Now, it is time... To DAAAAAAAANCE ! ! !" :
												"A philosopher is dead !!!");
}
