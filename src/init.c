#include "../include/hello.h"

static void		ft_create_main_menu(int data1, t_main_menu **menu)
{
	int i;

	g_gmode = ALL_WINDOWS;
	(*menu)->items = ft_memalloc(9 * sizeof(WINDOW*));
	*(*menu)->items = newwin(10,20,((*menu)->ss.y / 2) - 5,
			((*menu)->ss.x / 2) - 10);
	wbkgd(*(*menu)->items, COLOR_PAIR(1));
	i = 0;
	while (++i < 9)
	{
		(*menu)->items[i] = subwin(*(*menu)->items,1, 20,
				((*menu)->ss.y/ 2) - 5 + i + (i < 7 ? -1 : 1), ((*menu)->ss.x / 2) - 10);
		ft_print_define((*menu)->items[i], i);
	}
	wbkgd((*menu)->items[data1], COLOR_PAIR(2));
	wrefresh(*(*menu)->items);
}

void		ft_init_main_menu(bool lock_mutex, int data1, t_main_menu **menu)
{
	lock_mutex ? pthread_mutex_lock(&g_gmutex) : 0;
	*menu = ft_memalloc(sizeof(t_main_menu));
	(*menu)->y_pos = data1;
	getmaxyx(stdscr, (*menu)->ss.y, (*menu)->ss.x);
	if ((*menu)->ss.y > 10 && (*menu)->ss.x > 20)
		ft_create_main_menu(data1, menu);
	else
	{
		g_gmode = NOTHING_WINDOW;
		bkgd(COLOR_PAIR(2));
		refresh();
	}
	lock_mutex ? pthread_mutex_unlock(&g_gmutex) : 0;
}

void ft_init_curses(void)
{
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
	keypad(stdscr,FALSE);
	bkgd(COLOR_PAIR(1));
	refresh();
}

static void	ft_init_begin_game(t_philo_mother **mother, t_philo_heart **philo_heart)
{
	pthread_t			thread;
	int					count;
	char				*str1;

	count = -1;
	*mother = ft_memalloc(sizeof(t_philo_mother));
	//ft_sprintf(&(*mother)->result, "The game starts\n");
	str1 = ft_strjoin((*mother)->result, "The game starts\n");
	free((*mother)->result);
(*mother)->result = str1;
	ft_handle_mother_addr(mother, INIT);
	(*mother)->all_in_life = ft_handle_define(GET_INFOS, LIFE, 0) > 0 ?
																true : false;
	getmaxyx(stdscr, (*mother)->ss.y, (*mother)->ss.x);
	g_gmode = (*mother)->ss.y >= 30 && (*mother)->ss.x >= 82 ? ALL_WINDOWS : NOTHING;
	ft_get_name(INIT);
	ft_handle_wand_location(NULL, INIT, (*mother)->ss);
	(*mother)->win = ft_create_mother_window((*mother)->ss.y, (*mother)->ss.x);
	ft_print_game_var(mother, true);
	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
		ft_create_wand(philo_heart, (*mother)->ss);
	while (--count >= 0)
		ft_create_philo(philo_heart, (*mother)->ss);
	(*mother)->heart = *philo_heart;
	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
	{
		pthread_create(&thread, NULL, ft_philo, mother);
		pthread_detach(thread);
	}
}

void	ft_init_and_begin_game(void)
{
	int					count;
	t_philo_heart		*philo_heart;
	t_philo_mother		*mother;

	philo_heart = NULL;
	remove(RESULT);
	ft_init_begin_game(&mother, &philo_heart);
	count = 0;
	if (g_gmode == ALL_WINDOWS)
		while (count < ft_handle_define(GET_INFOS, NBPHILO, 0))
		{
			if (philo_heart->type == WAND &&
									!((t_wand*)philo_heart->data)->locate->init)
				count += ft_print_wand(philo_heart, mother, true);
			philo_heart = (philo_heart)->next;
		}
	ft_main_loop(&mother);
}
