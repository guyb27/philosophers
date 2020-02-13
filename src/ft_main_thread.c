#include "../include/hello.h"

void	ft_creat_menu(WINDOW ***menu, int x, int y, int color)
{
	int		i;

	i = 0;
	*menu = (WINDOW**)malloc(sizeof(WINDOW*) * 5);
	(*menu)[0] = newwin(6, 20, (y / 2) - 2, (x / 2) - 10);
	wbkgd((*menu)[0], COLOR_PAIR(color == 7 ? 6 : 5));
	box((*menu)[0], '|', '-');
	while(++i < 5)
		(*menu)[i] = subwin((*menu)[0], 1, 18, (y / 2) - (2 - i), (x / 2) - (10 - 1));
	wbkgd((*menu)[1], COLOR_PAIR(color));
	wprintw((*menu)[1], "Try again");
	wprintw((*menu)[2], "Main menu");
	wprintw((*menu)[3], "Cancel");
	wprintw((*menu)[4], "Quit");
	wrefresh((*menu)[0]);
}

int		ft_cancel(WINDOW ***menu, int ret)
{
	for (int i = 0;i<5;i++)
		delwin((*menu)[i]);
	wclear((*menu)[0]);
	wbkgd((*menu)[0], COLOR_PAIR(1));
	wrefresh((*menu)[0]);
	free(*menu);
	return (ret);
}

void	ft_vertical_keys(WINDOW ***menu, int *selected, int key, int color)
{
	wbkgd((*menu)[*selected + 1], COLOR_PAIR(color == 7 ? 6 : 5));
	wnoutrefresh((*menu)[*selected + 1]);
	if (key == KEY_DOWN)
		*selected = (*selected + 1) % 4;
	else
		*selected = (*selected - 1 + 4) % 4;
	wbkgd((*menu)[*selected + 1], COLOR_PAIR(color));
	wnoutrefresh((*menu)[*selected + 1]);
	doupdate();
}

int		ft_end_menu(int x, int y, int color)
{
	WINDOW **menu;
	int		key;
	int selected = 0;

	key = 0;
	ft_creat_menu(&menu, x, y, color);
	while (1)
	{
		key = getch();
		if (key == ENTER || key == ESCAPE)
		{
			if (selected + 1 == 1 && !(key == ESCAPE))
				return (ft_cancel(&menu, 1));
			else if (selected + 1 == 2 && !(key == ESCAPE))
				return (ft_cancel(&menu, 2));
			else if (selected + 1 == 3 || key == ESCAPE)
				return (ft_cancel(&menu, 0));
			else if (selected + 1 == 4 && !(key == ESCAPE))
				return (ft_cancel(&menu, 3));
		}
		else if (key == KEY_DOWN || key == KEY_UP)
			ft_vertical_keys(&menu, &selected, key, color);
	}
	return (0);
}

void	ft_end_game(char *str, t_philo_mother *mother)
{
	int			key;
	int			ret;
	bool		all_in_life;

	ret = 0;
	all_in_life = mother->all_in_life;
	mother->all_in_life = false;
	usleep(SEC);
	pthread_mutex_lock(&g_gmutex);
	mother->state_game = subwin(mother->win, 1, mother->ss.x, mother->ss.y - 1, 0);
	wbkgd(mother->state_game, COLOR_PAIR(all_in_life ? 6 : 5));
	wmove(mother->state_game, 0, (mother->ss.x / 2) - (ft_strlen(str) / 2));
	wprintw(mother->state_game, str);
	wrefresh(mother->state_game);
	pthread_mutex_unlock(&g_gmutex);
	keypad(stdscr, TRUE);
	while (getch() != -1);
	key = 0;
	while (1)
	{
		key = getch();
		if (key == ENTER || key == SPACE)
			break ;
		else if (key == ESCAPE)
			if ((ret = ft_end_menu(mother->ss.x, mother->ss.y, all_in_life ? 7 : 8)) > 0)
				break ;
	}
	keypad(stdscr, FALSE);
	ft_free_philo_mother(mother);
	pthread_mutex_lock(&g_gmutex);
	touchwin(stdscr);
	refresh();
	ft_handle_mother_addr(NULL, INIT);
	pthread_mutex_unlock(&g_gmutex);
	if (ret == 1)
		ft_init_and_begin_game();
	else if (ret == 2)
		ft_init_and_begin_main_menu();
	else
		endwin();
}

void	ft_print_game_var(t_philo_mother **mother, bool mutex_lock)
{
	if (mutex_lock && g_gmode == ALL_WINDOWS)
		pthread_mutex_lock(&g_gmutex);
	if (g_gmode == ALL_WINDOWS || !mutex_lock)
	{
		(*mother)->win_game_var = subwin((*mother)->win, 5, 25, 1, (*mother)->ss.x - 26);
		wbkgd((*mother)->win_game_var, COLOR_PAIR(2));
		wmove((*mother)->win_game_var, 0, 0);
		wprintw((*mother)->win_game_var, "MAX_LIFE: %d",
										ft_handle_define(GET_INFOS, LIFE, 0));
		wmove((*mother)->win_game_var, 1, 0);
		wprintw((*mother)->win_game_var, "EAT_TIME: %d",
										ft_handle_define(GET_INFOS, EAT, 0));
		wmove((*mother)->win_game_var, 2, 0);
		wprintw((*mother)->win_game_var, "REST_TIME: %d",
										ft_handle_define(GET_INFOS, REST, 0));
		wmove((*mother)->win_game_var, 3, 0);
		wprintw((*mother)->win_game_var, "THINK_TIME: %d",
										ft_handle_define(GET_INFOS, THINK, 0));
		wmove((*mother)->win_game_var, 4, 0);
		wprintw((*mother)->win_game_var, "TIME LEFT: %d",
										ft_handle_define(GET_INFOS, TIME, 0));
		wrefresh((*mother)->win_game_var);
	}
	if (mutex_lock && g_gmode == ALL_WINDOWS)
		pthread_mutex_unlock(&g_gmutex);
}

void	ft_main_loop(t_philo_mother **mother)
{
	size_t			begin_time;
	size_t			now_time;
	char			*str;
	int				timeout;

	timeout = ft_handle_define(GET_INFOS, TIME, 0);
	str = NULL;
	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + timeout && (*mother)->all_in_life)
	{
		usleep(SEC);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", (timeout - (now_time - begin_time)) < 0 ? 0 : timeout - (now_time - begin_time));
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*mother)->win_game_var, str, X_TIMEOUT, Y_TIMEOUT);
		pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str);
	}
	ft_end_game((*mother)->all_in_life ? "Now, it is time... To DAAAAAAAANCE ! ! !"
										: "A philosopher is dead !!!", *mother);
}
