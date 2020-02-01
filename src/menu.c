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

void	ft_menu(int xmax, int ymax)
{
int i;
	WINDOW **items;
	items = (WINDOW**)malloc(9 * sizeof(WINDOW*));
	items[0] = newwin(10,20,(ymax / 2) - 5, (xmax / 2) - 10);
	wbkgd(items[0], COLOR_PAIR(1));
	items[1] = subwin(items[0],1, 20,(ymax / 2) - 5 + 0, (xmax / 2) - 10);
	items[2] = subwin(items[0],1, 20, (ymax / 2) - 5 + 1, (xmax / 2) - 10);
	items[3] = subwin(items[0],1, 20, (ymax / 2) - 5 + 2, (xmax / 2) - 10);
	items[4] = subwin(items[0],1, 20, (ymax / 2) - 5 + 3, (xmax / 2) - 10);
	items[5] = subwin(items[0],1, 20, (ymax / 2) - 5 + 4, (xmax / 2) - 10);
	items[6] = subwin(items[0],1, 20, (ymax / 2) - 5 + 5, (xmax / 2) - 10);
	items[7] = subwin(items[0],1, 20, (ymax / 2) - 5 + 8, (xmax / 2) - 10);
	items[8] = subwin(items[0],1, 20, (ymax / 2) - 5 + 9, (xmax / 2) - 10);
	for (i = 1;i < 9; i++)
		ft_print_define(items[i], i);
	wbkgd(items[1], COLOR_PAIR(2));
	wrefresh(items[0]);
	int key = 0;
	int selected = 0;
	while (1)
	{
		key = getch();
		if (key == KEY_DOWN || key == KEY_UP)
		{
			wbkgd(items[selected + 1],COLOR_PAIR(1));
			wnoutrefresh(items[selected + 1]);
			if (key == KEY_DOWN)
				selected = (selected + 1) % 8;
			else
				selected = (selected - 1 + 8) % 8;
			wbkgd(items[selected + 1],COLOR_PAIR(2));
			wnoutrefresh(items[selected + 1]);
			doupdate();
		}
		else if ((key == ENTER || key == KEY_RIGHT) && selected + 1 >= 7)
		{
			for (int i = 0;i < 9;i++)
				delwin(items[i]);
			free(items);
			touchwin(stdscr);
			refresh();
			if (selected + 1 == 7)
				break ;
			else
				exit(endwin());//CREER UNE FONCTION FT_EXIT();
		}
		else if ((key == KEY_RIGHT || key == KEY_LEFT) && !(selected + 1 >= 7))
		{
			int value = ft_handle_define(GET_INFOS, selected, 0);
			if (key == KEY_LEFT && value > 0)
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
		}
	}
}
