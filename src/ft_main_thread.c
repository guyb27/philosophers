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

void	ft_cancel(WINDOW ***menu)
{
	for (int i = 0;i<5;i++)
		delwin((*menu)[i]);
	free(*menu);
	touchwin(stdscr);
	refresh();
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

void	ft_end_menu(int x, int y, int color)
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
			{
				//RECOMMENCER
			}
			else if (selected + 1 == 2 && !(key == ESCAPE))
			{
				//MENU PRINCIPAL
			}
			else if (selected + 1 == 3 && !(key == ESCAPE))
			{
				ft_cancel(&menu);
				break ;
			}
			else if (selected + 1 == 4 || key == ESCAPE)
			{
				for (int i = 0;i<5;i++)
					delwin(menu[i]);
				free(menu);
				endwin();
				exit(0);
			}
			//ft_exit();
		}
		else if (key == KEY_DOWN || key == KEY_UP)
			ft_vertical_keys(&menu, &selected, key, color);
	}
}

void	ft_end_game(char *str)//AFFICHER 'NOW IT S TIME TO DANCE' EN DESSOUS D UNE COULEUR VOYANTE
{
	int			i;
	int			x, y;
	int			key;
	int			color;
	WINDOW		*end_window;

	color = g_all_in_life ? 7 : 8;
	getmaxyx(stdscr, y, x);
	end_window = subwin(stdscr, 1, x, y - 1, 0);
	wbkgd(end_window, COLOR_PAIR(g_all_in_life ? 6 : 5));
	g_all_in_life = false;
	wmove(end_window, 0, (x / 2) - (ft_strlen(str) / 2));
	wprintw(end_window, str);
	wrefresh(end_window);
	key = 0;
	while (1)
	{
		key = getch();
		if (key == ENTER || key == SPACE)
			break ;
		else if (key == ESCAPE)
			ft_end_menu(x, y, color);
	}
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
