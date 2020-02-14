#include "../include/hello.h"

void	ft_print_define(WINDOW *win, int i)
{
	if (i == 1)
		wprintw(win,"MAX_LIFE: %d", ft_handle_define(GET_INFOS, LIFE, 0));
	else if (i == 2)
		wprintw(win,"EAT_T: %d", ft_handle_define(GET_INFOS, EAT, 0));
	else if (i == 3)
		wprintw(win,"REST_T: %d", ft_handle_define(GET_INFOS, REST, 0));
	else if (i == 4)
		wprintw(win,"THINK_T: %d", ft_handle_define(GET_INFOS, THINK, 0));
	else if (i == 5)
		wprintw(win,"TIMEOUT: %d", ft_handle_define(GET_INFOS, TIME, 0));
	else if (i == 6)
		wprintw(win,"NB_PHILO: %d", ft_handle_define(GET_INFOS, NBPHILO, 0));
	else if (i == 7)
		wprintw(win,"Start");
	else if (i == 8)
		wprintw(win,"Quit");
}

int		ft_enter_key(int selected)
{
	ft_handle_main_menu(DEL, 0, true, NULL);
	if (selected + 1 == 7)
		return (1);
	else
		exit(endwin());
}

void	ft_horizontal_keys(int key, int selected)
{
	int value;

	if (g_gmode <= NOTHING_WINDOW)
		return ;
	pthread_mutex_lock(&g_gmutex);
	value = ft_handle_define(GET_INFOS, selected, 0);
	WINDOW	**items = ft_handle_main_menu(GET_INFOS, 0, true, NULL)->items;
	if (key == KEY_LEFT && ((value > 0 && (selected == 0 || selected == 4)) ||
	(value > 1 && (selected > 0 || selected < 4))))
	{
		value = ft_handle_define(ACTUALIZE, selected, value - 1);
		wmove(items[selected + 1], 0, 0);
		wclrtoeol(items[selected + 1]);
		ft_print_define(items[selected + 1], selected + 1);
		wrefresh(items[selected + 1]);
	}
	else if (key == KEY_RIGHT && value < 2147483647)
	{
		value = ft_handle_define(ACTUALIZE, selected, value + 1);
		wmove(items[selected + 1], 0, 0);
		wclrtoeol(items[selected + 1]);
		ft_print_define(items[selected + 1], selected + 1);
		wrefresh(items[selected + 1]);
	}
	pthread_mutex_unlock(&g_gmutex);
}

void	ft_menu(void)
{
	int key;
	int selected;

	selected = 0;
	ft_handle_main_menu(INIT, 1, true, NULL);
	keypad(stdscr, TRUE);
	while (getch() != -1);
	while (1)
	{
		key = getch();
		if (key == KEY_DOWN || key == KEY_UP)
			ft_handle_main_menu(Y_ACTUALIZE, key, true, &selected);
		else if ((key == ENTER || key == KEY_RIGHT) && selected + 1 >= 7)
		{
			if (!(ft_handle_main_menu(DEL, 0, true, NULL)) && selected + 1 == 7)
				break ;
			else
				exit(endwin());
		}
		else if ((key == KEY_RIGHT || key == KEY_LEFT) && !(selected + 1 >= 6))
			ft_horizontal_keys(key, selected);
		else if (key == 410)
			ft_handle_main_menu(ACTUALIZE_SCREEN, 0, true, NULL);
	}
}
