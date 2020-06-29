/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:08:55 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

int					ft_init_main_menu(bool lock_mutex, int data1,
															t_main_menu **menu)
{
	int				y;
	int				x;

	getmaxyx(stdscr, y, x);
	lock_mutex ? pthread_mutex_lock(&g_gmutex) : 0;
	*menu = ft_memalloc(sizeof(t_main_menu));
	(*menu)->y_pos = data1;
	(*menu)->ss.y = y;
	(*menu)->ss.x = x;
	ft_create_main_menu(data1, menu);
	keypad(stdscr, TRUE);
	lock_mutex ? pthread_mutex_unlock(&g_gmutex) : 0;
	return (0);
}

void				ft_init_curses(void)
{
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_RED, COLOR_WHITE);
	init_pair(4, COLOR_BLUE, COLOR_WHITE);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_CYAN, COLOR_MAGENTA);
	curs_set(0);
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr, FALSE);
	bkgd(COLOR_PAIR(1));
	refresh();
}

static void			ft_create_threads(t_philo_mother **mother, int count)
{
	pthread_t		thread;

	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
	{
		pthread_create(&thread, NULL, ft_philo, mother);
		pthread_detach(thread);
	}
}

static void			ft_init_begin_game(t_philo_mother **mother,
													t_philo_heart **philo_heart)
{
	int				count;

	count = -1;
	*mother = ft_memalloc(sizeof(t_philo_mother));
	ft_handle_mother_addr(mother, INIT);
	(*mother)->all_in_life = ft_handle_define(GET_INFOS, LIFE, 0) > 0 ?
																true : false;
	getmaxyx(stdscr, (*mother)->ss.y, (*mother)->ss.x);
	g_gmode = ALL_WINDOWS;
	ft_get_name(INIT);
	ft_handle_wand_location(NULL, INIT, (*mother)->ss);
	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
		ft_create_wand(philo_heart, (*mother)->ss);
	while (--count >= 0)
		ft_create_philo(philo_heart, (*mother)->ss);
	(*mother)->heart = *philo_heart;
	ft_create_threads(mother, count);
}

void				ft_init_and_begin_game(void)
{
	int				count;
	t_philo_heart	*philo_heart;
	t_philo_mother	*mother;

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
