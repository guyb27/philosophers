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
		wprintw(win,"Commencer");
	else if (i == 8)
		wprintw(win,"Quit");
}

void	ft_create_menu(WINDOW ***items, int xmax, int ymax)
{
	int i;

	*items = (WINDOW**)malloc(9 * sizeof(WINDOW*));
	**items = newwin(10,20,(ymax / 2) - 5, (xmax / 2) - 10);
	wbkgd(**items, COLOR_PAIR(1));
	i = 0;
	while (++i < 7)
	{
		(*items)[i] = subwin(**items,1, 20,(ymax / 2) - 5 +  i - 1, (xmax / 2) - 10);
		ft_print_define((*items)[i], i);
	}
	while (i < 9)
	{
		(*items)[i] = subwin(**items,1, 20,(ymax / 2) - 5 +  i + 1, (xmax / 2) - 10);
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
	if (selected + 1 == 7)
		return (1);
	else
		exit(endwin());//CREER UNE FONCTION FT_EXIT();
}

void	ft_horizontal_keys(WINDOW ***items, int key, int selected)
{
	int value;

	value = ft_handle_define(GET_INFOS, selected, 0);
	if (key == KEY_LEFT && value > 0)
	{
		value = ft_handle_define(ACTUALIZE, selected, value - 1);
		wmove((*items)[selected + 1], 0, 0);
		wclrtoeol((*items)[selected + 1]);
		ft_print_define((*items)[selected + 1], selected + 1);
		wrefresh((*items)[selected + 1]);
	}
	else if (key == KEY_RIGHT && value < 2147483647)
	{
		value = ft_handle_define(ACTUALIZE, selected, value + 1);
		wmove((*items)[selected + 1], 0, 0);
		wclrtoeol((*items)[selected + 1]);
		ft_print_define((*items)[selected + 1], selected + 1);
		wrefresh((*items)[selected + 1]);
	}
}

void	ft_menu(int xmax, int ymax)
{
	WINDOW **items;
	int key = 0;
	int selected = 0;

	ft_create_menu(&items, xmax, ymax);
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
}
