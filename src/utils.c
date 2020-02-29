/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:52 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 06:21:17 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	if (g_gmode == ALL_WINDOWS)
	{
		wmove(capsule, x, y);
		wclrtoeol(capsule);
		wprintw(capsule, data);
		wrefresh(capsule);
	}
}

void		ft_actualize_game(void)
{
	pthread_mutex_lock(&g_gmutex);
	g_gmode = NOTHING_WINDOW;
	bkgd(COLOR_PAIR(2));
	refresh();
	pthread_mutex_unlock(&g_gmutex);
}

void		ft_resize(int sig)
{
	void *mother_addr;

	if (sig != SIGWINCH)
		return ;
	mother_addr = ft_handle_mother_addr(NULL, GET_INFOS);
	if (mother_addr)
		ft_actualize_game();
	else if (ft_handle_main_menu(GET_INFOS, 0, true, NULL))
		ft_handle_main_menu(ACTUALIZE_SCREEN, 0, true, NULL);
}
