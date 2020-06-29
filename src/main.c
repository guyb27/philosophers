/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:45:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

void			*ft_handle_mother_addr(void *mother,
												enum e_handle_static_function h)
{
	static void	*store_mother = NULL;

	if (h == INIT)
		store_mother = mother;
	else if (h == GET_INFOS)
		return (store_mother);
	return (NULL);
}

void			ft_init_and_begin_main_menu(void)
{
	ft_menu();
	endwin();
	gui_init();
	ft_init_and_begin_game();
}

int				main(int ac, char **av)
{
	if (ft_catch_error(ac, av))
		return (1);
	g_gmode = ALL_WINDOWS;
	signal(SIGWINCH, ft_resize);
	pthread_mutex_init(&g_gmutex, NULL);
	ft_init_curses();
	ft_init_and_begin_main_menu();
	pthread_mutex_destroy(&g_gmutex);
	return (0);
}
