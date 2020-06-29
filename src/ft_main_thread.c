/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 05:17:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 06:00:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static void	ft_save_game_var(char **str)
{
	(void)str;
	/*ft_sprintf(str, "%s%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n\n",
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
			ft_handle_define(GET_INFOS, TIME, 0));*/
}

void		ft_print_game_var(t_philo_mother **mother, bool mutex_lock)
{//A retirer surement
	mutex_lock ? pthread_mutex_lock(&g_gmutex) : 0;
	ft_save_game_var(&(*mother)->result);
	mutex_lock ? pthread_mutex_unlock(&g_gmutex) : 0;
}

void		ft_main_loop(t_philo_mother **mother)
{
	int		timeout;

	timeout = ft_handle_define(GET_INFOS, TIME, 0);
	gui_main_loop(*mother, timeout);
//	endwin();
}
