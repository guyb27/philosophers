/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 05:09:35 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static void			ft_close_window(t_philo_heart *philo)
{
	if (philo->type == PHILO)
	{
		free(((t_philo*)philo->data)->locate);
		free(((t_philo*)philo->data)->name);
		free((t_philo*)philo->data);
	}
	else
	{
		free(((t_wand*)philo->data)->locate);
		free((t_wand*)philo->data);
	}
}

static void			ft_free_philo_heart(t_philo_heart *philo)
{
	int				i;
	t_philo_heart	*tmp;

	i = -1;
	while (++i < ft_handle_define(GET_INFOS, NBPHILO, 0) * 2)
	{
		tmp = philo;
		ft_close_window(philo);
		philo = philo->next;
		free(tmp);
	}
}

void				ft_free_philo_mother(t_philo_mother *mother)
{
	ft_free_philo_heart(mother->heart);
	touchwin(stdscr);
	free(mother);
}
