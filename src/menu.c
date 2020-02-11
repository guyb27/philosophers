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

void	ft_create_menu(WINDOW ***items, t_screen_size ss)
{
	int i;

	*items = (WINDOW**)malloc(9 * sizeof(WINDOW*));
	pthread_mutex_lock(&g_gmutex);
	**items = newwin(10,20,(ss.y / 2) - 5, (ss.x / 2) - 10);
	wbkgd(**items, COLOR_PAIR(1));
	i = 0;
	while (++i < 7)
	{
		(*items)[i] = subwin(**items,1, 20, (ss.y/ 2) - 5 +  i - 1,
															(ss.x / 2) - 10);
		ft_print_define((*items)[i], i);
	}
	while (i < 9)
	{
		(*items)[i] = subwin(**items,1, 20,(ss.y / 2) - 5 +  i + 1,
															(ss.x / 2) - 10);
		ft_print_define((*items)[i], i);
		i++;
	}
	wbkgd((*items)[1], COLOR_PAIR(2));
	wrefresh(**items);
	pthread_mutex_unlock(&g_gmutex);
}

WINDOW		**ft_handle_main_menu(e_handle_static_function h, int y_pos, bool lock_mutex)
{
	int i;
	static t_main_menu	*menu = NULL;

	if (h == INIT)
	{
		ft_dprintf(2, "BEGIN_INIT, MENU:[%p]\n", &menu);
		if (lock_mutex)
			pthread_mutex_lock(&g_gmutex);
		menu = ft_memalloc(sizeof(t_main_menu));
		getmaxyx(stdscr, menu->ss.y, menu->ss.x);
		menu->items = ft_memalloc(9 * sizeof(WINDOW*));
		*menu->items = newwin(10,20,(menu->ss.y / 2) - 5, (menu->ss.x / 2) - 10);
		wbkgd(*menu->items, COLOR_PAIR(1));
		i = 0;
		while (++i < 7)
		{
			menu->items[i] = subwin(*menu->items,1, 20, (menu->ss.y/ 2) - 5 +  i - 1,
														(menu->ss.x / 2) - 10);
			ft_print_define(menu->items[i], i);
		}
		while (i < 9)
		{
			menu->items[i] = subwin(*menu->items,1, 20,(menu->ss.y / 2) - 5 +  i + 1,
														(menu->ss.x / 2) - 10);
			ft_print_define(menu->items[i], i);
			i++;
		}
		wbkgd(menu->items[1], COLOR_PAIR(2));
		wrefresh(*menu->items);
		if (lock_mutex)
			pthread_mutex_unlock(&g_gmutex);
		ft_dprintf(2, "END_INIT, MENU:[%p]\n", &menu);
	}
	else if (h == ACTUALIZE_SCREEN)
	{
		ft_dprintf(2, "BEGIN_ACTUALIZE_SCREEN\n");
		if (lock_mutex)
			pthread_mutex_lock(&g_gmutex);
	//	ft_handle_main_menu(DEL, 0, false);
		for (int i = 0;i < 9;i++)
			delwin(menu->items[i]);
		free(menu->items);
		menu->items = NULL;
		free(menu);
		menu = NULL;
		touchwin(stdscr);
		refresh();
		endwin();
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
        keypad(stdscr,true);
        bkgd(COLOR_PAIR(1));
        refresh();
		//ft_handle_main_menu(INIT, 0, false);
		ft_dprintf(2, "BEGIN_INIT, MENU:[%p]\n", &menu);
		menu = ft_memalloc(sizeof(t_main_menu));
		getmaxyx(stdscr, menu->ss.y, menu->ss.x);
		//menu->ss.y = 50;
		//menu->ss.x = 50;
		menu->items = ft_memalloc(9 * sizeof(WINDOW*));
		*menu->items = newwin(10,20,(menu->ss.y / 2) - 5, (menu->ss.x / 2) - 10);
		ft_dprintf(2, "X:[%d], Y:[%d]\n", menu->ss.x, menu->ss.y);
		wbkgd(*menu->items, COLOR_PAIR(1));
		i = 0;
		while (++i < 7)
		{
			menu->items[i] = subwin(*menu->items,1, 20, (menu->ss.y/ 2) - 5 +  i - 1,
														(menu->ss.x / 2) - 10);
			ft_print_define(menu->items[i], i);
		}
		while (i < 9)
		{
			menu->items[i] = subwin(*menu->items,1, 20,(menu->ss.y / 2) - 5 +  i + 1,
														(menu->ss.x / 2) - 10);
			ft_print_define(menu->items[i], i);
			i++;
		}
		wbkgd(menu->items[1], COLOR_PAIR(2));
		wrefresh(*menu->items);
		if (lock_mutex)
			pthread_mutex_unlock(&g_gmutex);
		ft_dprintf(2, "END_INIT, MENU:[%p]\n", &menu);
		//if (lock_mutex)
		//	pthread_mutex_unlock(&g_gmutex);
		ft_dprintf(2, "END_ACTUALIZE_SCREEN\n");
		return (NULL);
	}
	else if (h == ACTUALIZE)
	{
		if (lock_mutex)
			pthread_mutex_lock(&g_gmutex);
		(void)y_pos;
		if (lock_mutex)
			pthread_mutex_unlock(&g_gmutex);
	}
	else if (h == GET_INFOS)
		return (menu->items);
	else if (h == DEL && menu && menu->items)
	{
		ft_dprintf(2, "BEGIN_DEL\n");
		if (lock_mutex)
			pthread_mutex_lock(&g_gmutex);
		for (int i = 0;i < 9;i++)
			delwin(menu->items[i]);
		free(menu->items);
		menu->items = NULL;
		free(menu);
		menu = NULL;
		touchwin(stdscr);
		refresh();
		keypad(stdscr, FALSE);
		if (lock_mutex)
			pthread_mutex_unlock(&g_gmutex);
		ft_dprintf(2, "END_DEL\n");
	}
	return (NULL);
}

void	ft_vertical_key(int *selected, int key)
{
	pthread_mutex_lock(&g_gmutex);
	WINDOW	**items = ft_handle_main_menu(GET_INFOS, 0, true);
	wbkgd(items[*selected + 1],COLOR_PAIR(1));
	wnoutrefresh(items[*selected + 1]);
	if (key == KEY_DOWN)
		*selected = (*selected + 1) % 8;
	else
		*selected = (*selected - 1 + 8) % 8;
	wbkgd(items[*selected + 1],COLOR_PAIR(2));
	wnoutrefresh(items[*selected + 1]);
	doupdate();
	pthread_mutex_unlock(&g_gmutex);
}

int		ft_enter_key(int selected)
{
	ft_handle_main_menu(DEL, 0, true);
	if (selected + 1 == 7)
		return (1);
	else
		exit(endwin());
}

void	ft_horizontal_keys(int key, int selected)
{
	int value;

	pthread_mutex_lock(&g_gmutex);
	value = ft_handle_define(GET_INFOS, selected, 0);
	WINDOW	**items = ft_handle_main_menu(GET_INFOS, 0, true);
	if (key == KEY_LEFT && value > 0 && (selected != 5 || value > 2))
	{
		value = ft_handle_define(ACTUALIZE, selected, value - 1);
		wmove(items[selected + 1], 0, 0);
		wclrtoeol(items[selected + 1]);
		ft_print_define(items[selected + 1], selected + 1);
		wrefresh(items[selected + 1]);
	}
	else if (key == KEY_RIGHT && value < 2147483647 &&
												(selected != 5 || value < 7))
	{
		value = ft_handle_define(ACTUALIZE, selected, value + 1);
		wmove(items[selected + 1], 0, 0);
		wclrtoeol(items[selected + 1]);
		ft_print_define(items[selected + 1], selected + 1);
		wrefresh(items[selected + 1]);
	}
	pthread_mutex_unlock(&g_gmutex);
}

void		ft_main_menu_resize(int sig)// /!\ N'a pas sa place dans le menu vu que c est global
{
	void *mother_addr;

	if (sig != SIGWINCH)
		return ;
	//t_screen_size	ss;
	mother_addr = ft_handle_mother_addr(NULL, GET_INFOS);
	if (mother_addr)
		ft_dprintf(2, "GAME: RESIZE_addr:[%p]\n", mother_addr);
	else if (ft_handle_main_menu(GET_INFOS, 0, true))
	{
		ft_handle_main_menu(ACTUALIZE_SCREEN, 0, true);
		ft_dprintf(2, "MAIN_MENU: RESIZE\n");
	}
}

void	ft_menu(void)
{
	int key;
	int selected;

	key = 0;
	selected = 0;
	ft_handle_main_menu(INIT, 0, true);
	signal(SIGWINCH, ft_main_menu_resize);
	keypad(stdscr, TRUE);
	while (getch() != -1);
	while (1)
	{
		key = getch();
		if (key == KEY_DOWN || key == KEY_UP)
			ft_vertical_key(&selected, key);
		else if ((key == ENTER || key == KEY_RIGHT) && selected + 1 >= 7)
		{
			if (ft_enter_key(selected))
				break ;
		}
		else if ((key == KEY_RIGHT || key == KEY_LEFT) && !(selected + 1 >= 7))
			//PRENDRE AU CAS PAR CAS ET SE REFERER A LA FONCTION ft_get_err_define_size();
			ft_horizontal_keys(key, selected);
	}
}
