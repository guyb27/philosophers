/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:52 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 11:58:04 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

void		ft_actualize_game(void)
{
	pthread_mutex_lock(&g_gmutex);
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

int			ft_change_value(int value, int selected, WINDOW **items)
{
	value = ft_handle_define(ACTUALIZE, selected, value + 1);
	wmove(items[selected + 1], 0, 0);
	wclrtoeol(items[selected + 1]);
	ft_print_define(items[selected + 1], selected + 1);
	wrefresh(items[selected + 1]);
	return (value);
}
