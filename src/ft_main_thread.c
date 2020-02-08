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
			{
				ft_cancel(&menu);
				return (1);
				//RECOMMENCER
			}
			else if (selected + 1 == 2 && !(key == ESCAPE))
			{
				ft_cancel(&menu);
				return (2);
				//MENU PRINCIPAL
			}
			else if (selected + 1 == 3 || key == ESCAPE)
			{
				ft_cancel(&menu);
				return (0);
			}
			else if (selected + 1 == 4 && !(key == ESCAPE))
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
	mother->state_game = subwin(mother->win, 1, mother->ss.x, mother->ss.y - 1, 0);
	wbkgd(mother->state_game, COLOR_PAIR(all_in_life ? 6 : 5));
	wmove(mother->state_game, 0, (mother->ss.x / 2) - (ft_strlen(str) / 2));
	wprintw(mother->state_game, str);
	pthread_mutex_lock(&mother->mutex);
	wrefresh(mother->state_game);
	pthread_mutex_unlock(&mother->mutex);
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
//	delwin(mother->win_game_var);
//	delwin(mother->state_game);
//	free(mother->win);
	ft_free_philo_mother(mother);
	pthread_mutex_lock(&mother->mutex);
	touchwin(stdscr);
	refresh();
	pthread_mutex_unlock(&mother->mutex);
	if (ret == 1)
		ft_init_and_begin_game();
	else if (ret == 2)
		ft_init_and_begin_main_menu();
}

void	ft_print_game_var(t_philo_mother *mother)
{
	mother->win_game_var = subwin(mother->win, 5, 25, 1, mother->ss.x - 26);
	wbkgd(mother->win_game_var, COLOR_PAIR(2));
	wmove(mother->win_game_var, 0, 0);
	wprintw(mother->win_game_var, "MAX_LIFE: ");
	wprintw(mother->win_game_var, ft_itoa(ft_handle_define(GET_INFOS, LIFE, 0)));
	wmove(mother->win_game_var, 1, 0);
	wprintw(mother->win_game_var, "EAT_TIME: ");
	wprintw(mother->win_game_var, ft_itoa(ft_handle_define(GET_INFOS, EAT, 0)));
	wmove(mother->win_game_var, 2, 0);
	wprintw(mother->win_game_var, "REST_TIME: ");
	wprintw(mother->win_game_var, ft_itoa(ft_handle_define(GET_INFOS, REST, 0)));
	wmove(mother->win_game_var, 3, 0);
	wprintw(mother->win_game_var, "THINK_TIME: ");
	wprintw(mother->win_game_var, ft_itoa(ft_handle_define(GET_INFOS, THINK, 0)));
	wmove(mother->win_game_var, 4, 0);
	wprintw(mother->win_game_var, "TIME LEFT: ");
	wprintw(mother->win_game_var, ft_itoa(ft_handle_define(GET_INFOS, TIME, 0)));
	pthread_mutex_lock(&mother->mutex);
	wrefresh(mother->win_game_var);
	pthread_mutex_unlock(&mother->mutex);
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
		ft_sprintf(&str, "%zi", timeout - (now_time - begin_time));
		pthread_mutex_lock(&(*mother)->mutex);
		ft_actualize((*mother)->win_game_var, str, X_TIMEOUT, Y_TIMEOUT);
		pthread_mutex_unlock(&(*mother)->mutex);
		ft_strdel(&str);
	}
	ft_end_game((*mother)->all_in_life ? "Now, it is time... To DAAAAAAAANCE ! ! !" :
			"A philosopher is dead !!!", *mother);
}
