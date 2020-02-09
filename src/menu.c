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
}

void	ft_vertical_key(WINDOW ***items, int *selected, int key)
{
	wbkgd((*items)[*selected + 1],COLOR_PAIR(1));
	wnoutrefresh((*items)[*selected + 1]);
	if (key == KEY_DOWN)
		*selected = (*selected + 1) % 8;
	else
		*selected = (*selected - 1 + 8) % 8;
	wbkgd((*items)[*selected + 1],COLOR_PAIR(2));
	wnoutrefresh((*items)[*selected + 1]);
	doupdate();
}

int		ft_enter_key(WINDOW ***items, int selected)
{
	for (int i = 0;i < 9;i++)
		delwin((*items)[i]);
	free(*items);
	touchwin(stdscr);
	refresh();
	keypad(stdscr, FALSE);
	if (selected + 1 == 7)
		return (1);
	else
	{
		endwin();
		exit(0);
	}
}

void	ft_horizontal_keys(WINDOW ***items, int key, int selected)
{
	int value;

	value = ft_handle_define(GET_INFOS, selected, 0);
	if (key == KEY_LEFT && value > 0 && (selected != 5 || value > 2))
	{
		value = ft_handle_define(ACTUALIZE, selected, value - 1);
		wmove((*items)[selected + 1], 0, 0);
		wclrtoeol((*items)[selected + 1]);
		ft_print_define((*items)[selected + 1], selected + 1);
		wrefresh((*items)[selected + 1]);
	}
	else if (key == KEY_RIGHT && value < 2147483647 &&
												(selected != 5 || value < 7))
	{
		value = ft_handle_define(ACTUALIZE, selected, value + 1);
		wmove((*items)[selected + 1], 0, 0);
		wclrtoeol((*items)[selected + 1]);
		ft_print_define((*items)[selected + 1], selected + 1);
		wrefresh((*items)[selected + 1]);
	}
}

void		*ft_handle_main_menu_addr(void *main_menu, e_handle_static_function h)
{
	static void	*store_main_menu = NULL;

	if (h == INIT)
		store_main_menu = main_menu;
	else if (h == GET_INFOS)
		return (store_main_menu);
	return (NULL);
}

void		ft_main_menu_resize(int i)
{
	void *mother_addr = ft_handle_mother_addr(NULL, GET_INFOS);
	void *main_menu_addr = ft_handle_main_menu_addr(NULL, GET_INFOS);
	if (mother_addr)
		ft_dprintf(2, "GAME: RESIZE: [%d], addr:[%p]\n", i, mother_addr);
	else
		ft_dprintf(2, "MAIN_MENU: RESIZE: [%d], addr:[%p]\n", i, main_menu_addr);
}

void	ft_menu(void)
{
	WINDOW **items;
	int key;
	int selected;
	t_screen_size	ss;

	key = 0;
	selected = 0;
	items = NULL;
	ft_handle_main_menu_addr(&items, INIT);
	getmaxyx(stdscr, ss.y, ss.x);
	if (ss.y > 10 && ss.x > 20)
		ft_create_menu(&items, ss);
	else
	{
		endwin();
		ft_dprintf(2, "%sError: Terminal size too small.\%s\n", RED, STOP);
		exit(1);
	}
	signal(SIGWINCH, ft_main_menu_resize);
	keypad(stdscr, TRUE);
	while (getch() != -1);
	while (1)
	{
		key = getch();
		if (key == KEY_DOWN || key == KEY_UP)
			ft_vertical_key(&items, &selected, key);
		else if ((key == ENTER || key == KEY_RIGHT) && selected + 1 >= 7)
		{
			if (ft_enter_key(&items, selected))
				break ;
		}
		else if ((key == KEY_RIGHT || key == KEY_LEFT) && !(selected + 1 >= 7))
			//PRENDRE AU CAS PAR CAS ET SE REFERER A LA FONCTION ft_get_err_define_size();
			ft_horizontal_keys(&items, key, selected);
	}
	ft_handle_main_menu_addr(NULL, INIT);
}
