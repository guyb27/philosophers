#include "../include/hello.h"

static void			ft_actualize_screen(bool lock_mutex, int actual_ypos)
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

static void			ft_y_actualize(bool lock_mutex, int data1, int *data2, t_main_menu **menu)
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

static void			ft_del_menu(bool lock_mutex, t_main_menu **menu)
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
