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

void		ft_main_loop(t_philo_mother **mother)
{
	int		timeout;

	timeout = ft_handle_define(GET_INFOS, TIME, 0);
	gui_main_loop(*mother, timeout);
	ft_free_philo_mother(*mother);
}
