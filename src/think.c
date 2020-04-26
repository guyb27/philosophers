/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 11:31:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static size_t	ft_think_begin_actualize(t_philo_heart **philo, int wand,
														t_philo_mother **mother)
{
	char		*str;
	char		*str1;

	pthread_mutex_lock(&g_gmutex);
	str1 = ft_strjoin_free((*mother)->result, ((t_philo*)(*philo)->data)->name);
	(*mother)->result = ft_strjoin_free(str1, " is thinking");
	if (wand == LEFT)
	{
		if (((t_wand*)(*philo)->prev->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, THINK_RIGHT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	}
	else
	{
		if (((t_wand*)(*philo)->next->data)->wand_state == FREE)
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, THINK_LEFT);
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	}
	ft_sprintf(&str, "%zi", ft_handle_define(GET_INFOS, THINK, 0));
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "REFLECHIS",
															X_STATE, Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	return (time(NULL));
}

static void		ft_think_end_actualize(t_philo_heart **philo, int wand,
														t_philo_mother **mother)
{
	if (wand == LEFT &&
			((t_wand*)(*philo)->prev->data)->wand_state == THINK_LEFT)
	{
		((t_wand*)(*philo)->prev->data)->wand_state = FREE;
		if ((*mother)->all_in_life)
		{
			pthread_mutex_lock(&g_gmutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->prev, FREE);
			pthread_mutex_unlock(&g_gmutex);
		}
	}
	else if (wand == RIGHT &&
			((t_wand*)(*philo)->next->data)->wand_state == THINK_RIGHT)
	{
		((t_wand*)(*philo)->next->data)->wand_state = FREE;
		if ((*mother)->all_in_life)
		{
			pthread_mutex_lock(&g_gmutex);
			ft_actualize_wand((t_philo_heart**)&(*philo)->next, FREE);
			pthread_mutex_unlock(&g_gmutex);
		}
	}
}

static void		ft_think_mid_actualize(t_philo **data, char *str[],
								t_philo_heart **philo, t_philo_mother **mother)
{
	char		*str1;

	pthread_mutex_lock(&g_gmutex);
	ft_actualize((*data)->capsule, str[0], X_TIME, Y_TIME);
	ft_actualize((*data)->capsule, str[1], X_LIFE, Y_LIFE);
	if (!(size_t)((t_philo*)(*philo)->data)->life)
	{
		ft_sprintf(&str1, "%s%s est mort\n", (*mother)->result,
															(*data)->name);
		free((*mother)->result);
		(*mother)->result = str1;
		(*mother)->all_in_life = false;
	}
	pthread_mutex_unlock(&g_gmutex);
}

int				ft_wand_is_stealable(t_philo_heart **philo, int direction)
{
	if (direction == 0 && ((t_wand*)(*philo)->prev->data)->reserved == LEFT &&
	((t_philo*)(*philo)->prev->prev->data)->life > ((t_philo*)(*philo)->data)->life)
		return (1);
	else if (direction == 0 && ((t_wand*)(*philo)->prev->data)->reserved == NOTHING)
		return (1);
	else if (direction == 1 && ((t_wand*)(*philo)->next->data)->reserved == RIGHT &&
	((t_philo*)(*philo)->next->next->data)->life > ((t_philo*)(*philo)->data)->life)
		return (1);
	else if (direction == 1 && ((t_wand*)(*philo)->next->data)->reserved == RIGHT)
		return (1);
	return (0);
	
}

int				ft_wand_is_reserbable(t_philo_heart **philo, int direction)
{
	int				ret;

	ret = 0;
	if (direction == 0 && !pthread_mutex_trylock(&((t_wand*)(*philo)->prev->data)->mutex))
	{
		if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
		ft_dprintf(2, "%sWand droite%s,%s TRY_LOCK: %s[%s]\n", GREENB, STOP, BLUE, STOP, ((t_philo*)(*philo)->data)->name);
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
		ret = 1;
	}
	if (direction == 1 && !pthread_mutex_trylock(&((t_wand*)(*philo)->next->data)->mutex))
	{
		if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
			ft_dprintf(2, "%sWand gauche%s,%s TRY_LOCK: %s[%s]\n", GREENB, STOP, BLUE, STOP, ((t_philo*)(*philo)->data)->name);
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
		ret = 1;
	}
	else if (direction == 0 && ((t_philo*)(*philo)->prev->data)->time <= 1)
	{
		if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
		ft_dprintf(2, "%sWand droite%s,%s TIME <= 1: %s[%s]\n", GREENB, STOP, BLUE, STOP, ((t_philo*)(*philo)->data)->name);
		ret = 2;
	}
	else if (direction == 1 && ((t_philo*)(*philo)->next->data)->time <= 1)
	{
		if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
			ft_dprintf(2, "%sWand gauche%s,%s TIME <= 1: %s[%s]\n", GREENB, STOP, BLUE, STOP, ((t_philo*)(*philo)->data)->name);
		ret = 2;
	}
	else if (direction == 0 && !ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
			ft_dprintf(2, "%sWand droite%s,%s Is_not_reserbable: %s[%s]\n", REDB, STOP, BLUE, STOP, ((t_philo*)(*philo)->data)->name);
	else if (direction == 1 && !ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
			ft_dprintf(2, "%sWand gauche%s,%s Is_not_reserbable: %s[%s]\n", REDB, STOP, BLUE, STOP, ((t_philo*)(*philo)->data)->name);
	if (ret && ft_wand_is_stealable(philo, direction))
	{
		ret = 1;
	}
	else
	{
		ret = 0;
	}
	return (ret);
}

void				ft_left_reservation(t_philo_heart **philo)
{
	((t_wand*)(*philo)->next->data)->reserved = NOTHING;
	((t_wand*)(*philo)->prev->data)->reserved = NOTHING;
}

void			ft_reserve_wand(t_philo_heart **philo)
{
	int			is_reseved;

	is_reseved = 0;
	//if (((t_wand*)(*philo)->next->data)->reserved == RIGHT &&
	//((t_philo*)(*philo)->next->next->data)->life > ((t_philo*)(*philo)->data)->life)
	if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
		ft_dprintf(2, "-----------------------\n");
	if (ft_wand_is_reserbable(philo, 1))
	{
//		if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
//			ft_dprintf(2, "%sWand droite%s is_reserbable: [%s]\n", GREENB, STOP, ((t_philo*)(*philo)->data)->name);
		is_reseved++;
	}
//	else if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
//		ft_dprintf(2, "%sWand droite%s%s is_not_available: %s[%s]\n", GREENB, STOP, RED, STOP, ((t_philo*)(*philo)->data)->name);
	//if (((t_wand*)(*philo)->prev->data)->reserved == LEFT &&
	//((t_philo*)(*philo)->prev->prev->data)->life > ((t_philo*)(*philo)->data)->life)
	if (ft_wand_is_reserbable(philo, 0))
	{
//		if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
//			ft_dprintf(2, "%sWand gauche%s is_reserbable: [%s]\n", YELLOWB, STOP, ((t_philo*)(*philo)->data)->name);
		is_reseved++;
	}
//	else if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
//		ft_dprintf(2, "%sWand gauche%s is_not_available: %s[%s]\n", YELLOWB, RED, STOP, ((t_philo*)(*philo)->data)->name);
	if (is_reseved == 2)
	{
		((t_wand*)(*philo)->next->data)->reserved = LEFT;
		((t_wand*)(*philo)->prev->data)->reserved = RIGHT;
	}
}

int				ft_think(int ret, t_philo_heart **philo, t_philo **data,
														t_philo_mother **mother)
{
	size_t		begin_time;
	size_t		now_time;
	char		*str[2];
	int			think_t;

	think_t = ft_handle_define(GET_INFOS, THINK, 0);
	begin_time = ft_think_begin_actualize(philo, ret, mother);
	now_time = begin_time;
	while (now_time <= begin_time + think_t && (*mother)->all_in_life)
	{
		((t_philo*)(*philo)->data)->time = begin_time + think_t - now_time;
		if (((t_philo*)(*philo)->data)->time <= 1)//√
		{
			//if (!ft_strcmp(((t_philo*)(*philo)->data)->name, "Socrate"))
			//	ft_dprintf(2, "%sTIME, [%s]: [%zi]%s\n", PURPLEB, ((t_philo*)(*philo)->data)->name, ((t_philo*)(*philo)->data)->time, STOP);
			pthread_mutex_lock(&g_gmutex);
			//ft_dprintf(2, "[%s]: [%zi]\n", ((t_philo*)(*philo)->data)->name, ((t_philo*)(*philo)->data)->time);
			//RESERVE WAND
			ft_reserve_wand(philo);
			pthread_mutex_unlock(&g_gmutex);
		}
		usleep(SEC);
		(*data)->life--;
		time((time_t*)&now_time);
		ft_sprintf(&str[0], "%zi", (int)((begin_time + think_t) - now_time) >
				0 ? (begin_time + think_t) - now_time : 0);
		ft_sprintf(&str[1], "%d", (*data)->life);
		ft_think_mid_actualize(data, str, philo, mother);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
	}
	ft_think_end_actualize(philo, ret, mother);
	return (0);
}
