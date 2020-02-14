#include "../include/hello.h"

static int	ft_init_end_menu(char *str, t_philo_mother *mother, bool all_in_life)
{
	int			key;
	int			ret;

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
	while (g_gmode == ALL_WINDOWS)
	{
		key = getch();
		if (key == ENTER || key == SPACE)
			return (0);
		else if (key == ESCAPE)
			if ((ret = ft_end_menu(mother->ss.x, mother->ss.y, all_in_life ? 7 :
																		8)) > 0)
				return (ret);
	}
	return (0);
}

static void	ft_end_game(char *str, t_philo_mother *mother)
{
	int			ret;
	bool		all_in_life;

	ret = 0;
	all_in_life = mother->all_in_life;
	mother->all_in_life = false;
	usleep(SEC);
	ft_sprintf(&mother->result, "%s%s%s%s\n", mother->result, all_in_life ?
			GREEN : RED, str, STOP);
	if (g_gmode == ALL_WINDOWS)
		ret = ft_init_end_menu(str, mother, all_in_life);
	ft_fprintf(RESULT, "%s", mother->result);
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

static void	ft_save_game_var(char **str)
{
	ft_sprintf(str, "%s%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n\n",
			(*str),
			"MAX_LIFE: ",
			ft_handle_define(GET_INFOS, LIFE, 0),
			"EAT_TIME: ",
			ft_handle_define(GET_INFOS, EAT, 0),
			"REST_TIME: ",
			ft_handle_define(GET_INFOS, REST, 0),
			"THINK_TIME: ",
			ft_handle_define(GET_INFOS, THINK, 0),
			"TIME_LEFT: ",
			ft_handle_define(GET_INFOS, TIME, 0)
			);
}

void	ft_print_game_var(t_philo_mother **mother, bool mutex_lock)
{
	mutex_lock ? pthread_mutex_lock(&g_gmutex) : 0;
	ft_save_game_var(&(*mother)->result);
	if (g_gmode == ALL_WINDOWS || !mutex_lock)
	{
		(*mother)->win_game_var = subwin((*mother)->win, 5, 25, 1,
				(*mother)->ss.x - 26);
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
	mutex_lock ? pthread_mutex_unlock(&g_gmutex) : 0;
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
		ft_sprintf(&str, "%zi", (timeout - (now_time - begin_time)) < 0 ? 0 :
				timeout - (now_time - begin_time));
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*mother)->win_game_var, str, X_TIMEOUT, Y_TIMEOUT);
		pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str);
	}
	ft_end_game((*mother)->all_in_life ?
			"Now, it is time... To DAAAAAAAANCE ! ! !"
			: "A philosopher is dead !!!", *mother);
}
