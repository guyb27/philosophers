/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_define.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:56:48 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static int		ft_handle_def_others(enum e_handle_static_function h,
												enum e_define_type d, int value)
{
	static int	nb_philo = NB_PHILO;
	static int	max_life = MAX_LIFE;

	if (h == ACTUALIZE && value >= 0)
	{
		if (d == NBPHILO)
			return (nb_philo = value);
		else if (d == LIFE)
			return (max_life = value);
		else
			return (-1);
	}
	if (h == GET_INFOS && (d == NBPHILO || d == LIFE))
		return (d == NBPHILO ? nb_philo : max_life);
	return (-1);
}

static int		ft_handle_def_time(enum e_handle_static_function h,
											enum e_define_type d, int value)
{
	static int	eat_t = EAT_T;
	static int	think_t = THINK_T;
	static int	rest_t = REST_T;
	static int	timeout = TIMEOUT;

	if (h == ACTUALIZE && value >= 0)
	{
		if (d == EAT)
			return (eat_t = value);
		else if (d == REST)
			return (rest_t = value);
		else if (d == THINK)
			return (think_t = value);
		else if (d == TIME)
			return (timeout = value);
		else
			return (-1);
	}
	if (h == GET_INFOS && (d == EAT || d == REST))
		return (d == EAT ? eat_t : rest_t);
	else if (h == GET_INFOS && (d == THINK || d == TIME))
		return (d == THINK ? think_t : timeout);
	return (-1);
}

int				ft_handle_define(enum e_handle_static_function h,
												enum e_define_type d, int value)
{
	if (d == NBPHILO || d == LIFE)
		return (ft_handle_def_others(h, d, value));
	else
		return (ft_handle_def_time(h, d, value));
}
