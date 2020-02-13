#include "../include/hello.h"

void		ft_init_main_menu(bool lock_mutex, int data1, t_main_menu **menu)
{
	int i;

	if (lock_mutex)
		pthread_mutex_lock(&g_gmutex);
	*menu = ft_memalloc(sizeof(t_main_menu));
	(*menu)->y_pos = data1;
	getmaxyx(stdscr, (*menu)->ss.y, (*menu)->ss.x);
	if ((*menu)->ss.y > 10 && (*menu)->ss.x > 20)
	{
		g_gmode = ALL_WINDOWS;
		(*menu)->items = ft_memalloc(9 * sizeof(WINDOW*));
		*(*menu)->items = newwin(10,20,((*menu)->ss.y / 2) - 5,
														((*menu)->ss.x / 2) - 10);
		wbkgd(*(*menu)->items, COLOR_PAIR(1));
		i = 0;
		while (++i < 9)
		{
			(*menu)->items[i] = subwin(*(*menu)->items,1, 20, ((*menu)->ss.y/ 2) -
								5 + i + (i < 7 ? -1 : 1), ((*menu)->ss.x / 2) - 10);
			ft_print_define((*menu)->items[i], i);
		}
		wbkgd((*menu)->items[data1], COLOR_PAIR(2));
		wrefresh(*(*menu)->items);
	}
	else
	{
		g_gmode = NOTHING_WINDOW;
		bkgd(COLOR_PAIR(2));
		refresh();
	}
	if (lock_mutex)
		pthread_mutex_unlock(&g_gmutex);
}

void			ft_actualize_screen(bool lock_mutex, int actual_ypos)
{
	int		tmp;

	if (lock_mutex)
		pthread_mutex_lock(&g_gmutex);
	tmp = actual_ypos;
	ft_handle_main_menu(DEL, 0, false, NULL);
	endwin();
	ft_init_curses();
	ft_handle_main_menu(INIT, tmp, false, NULL);
	keypad(stdscr,true);
	if (lock_mutex)
		pthread_mutex_unlock(&g_gmutex);
}

void			ft_y_actualize(bool lock_mutex, int data1, int *data2, t_main_menu **menu)
{
	if (g_gmode <= NOTHING_WINDOW)
		return ;
	if (lock_mutex)
		pthread_mutex_lock(&g_gmutex);
	wbkgd((*menu)->items[*(int*)(int*)data2 + 1],COLOR_PAIR(1));
	wnoutrefresh((*menu)->items[*(int*)data2 + 1]);
	if (data1 == KEY_DOWN)
		*(int*)data2 = (*(int*)data2 + 1) % 8;
	else
		*(int*)data2 = (*(int*)data2 - 1 + 8) % 8;
	(*menu)->y_pos = *(int*)data2 + 1;
	wbkgd((*menu)->items[*(int*)data2 + 1],COLOR_PAIR(2));
	wnoutrefresh((*menu)->items[*(int*)data2 + 1]);
	doupdate();
	if (lock_mutex)
		pthread_mutex_unlock(&g_gmutex);
}

void			ft_del_menu(bool lock_mutex, t_main_menu **menu)
{
	if (lock_mutex)
		pthread_mutex_lock(&g_gmutex);
	for (int i = 0;i < 9;i++)
		delwin((*menu)->items[i]);
	free((*menu)->items);
	(*menu)->items = NULL;
	free(*menu);
	menu = NULL;
	keypad(stdscr, FALSE);
	touchwin(stdscr);
	refresh();
	if (lock_mutex)
		pthread_mutex_unlock(&g_gmutex);
}

t_main_menu		*ft_handle_main_menu(e_handle_static_function h, int data1, bool lock_mutex, void *data2)
{
	static t_main_menu	*menu = NULL;

	if (h == INIT)
		ft_init_main_menu(lock_mutex, data1, &menu);
	else if (h == ACTUALIZE_SCREEN)
		ft_actualize_screen(lock_mutex, menu->y_pos);
	else if (h == Y_ACTUALIZE)
		ft_y_actualize(lock_mutex, data1, data2, &menu);
	else if (h == GET_INFOS)
		return (menu);
	else if (h == DEL && menu && menu->items)
		ft_del_menu(lock_mutex, &menu);
	return (NULL);
}
