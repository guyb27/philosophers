/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:48:55 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

int					ft_is_available(t_wand *wand)
{
	int ret = 0;
	//pthread_mutex_lock(&g_gmutex);
	ret = pthread_mutex_trylock(&wand->mutex);
	if (ret)
		pthread_mutex_unlock(&wand->mutex);
	//pthread_mutex_unlock(&g_gmutex);
	return (ret);
}

void				ft_left_reservation(t_philo_heart **philo)
{
	((t_wand*)(*philo)->next->data)->reserved = NOTHING;
	((t_wand*)(*philo)->prev->data)->reserved = NOTHING;
}

void				ft_reserve_wands(t_philo_heart **philo)
{
	int is_get = 0;
	int left = ft_is_available((t_wand*)(*philo)->prev->data);
	int right = ft_is_available((t_wand*)(*philo)->next->data);
	if ((right || left))
	{
			
		ft_dprintf(2, "%s0RESERVE_WAND%s: (%s), L: %d, R: %d%s\n", YELLOW, RED, ((t_philo*)(*philo)->data)->name, left, right, STOP);
		return ;
	}
	char *str;
	ft_sprintf(&str, "%s1RESERVE_WAND%s: (%s)", YELLOW, GREEN, ((t_philo*)(*philo)->data)->name);
	//else
		if (((t_wand*)(*philo)->next->data)->reserved == RIGHT)
		{
			if (((t_philo*)(*philo)->next->next->data)->life > (((t_philo*)(*philo)->data)->life))//Le philo next a plus(+) de vie
			{
				ft_sprintf(&str, "%s, R:GET", str);
				is_get++;
			}
			else
				ft_sprintf(&str, "%s, R: NOT", str);
		}
		else
		{
			is_get++;
			ft_sprintf(&str, "%s, R:GET", str);
		}
		if (((t_wand*)(*philo)->prev->data)->reserved == LEFT)
		{
			if (((t_philo*)(*philo)->prev->prev->data)->life > (((t_philo*)(*philo)->data)->life))//Le philo prev a plus(+) de vie
			{
				is_get++;
				ft_sprintf(&str, "%s, R:GET", str);
			}
			else
				ft_sprintf(&str, "%s, R:NOT", str);
		}
		else
		{
			is_get++;
			ft_sprintf(&str, "%s, R:GET", str);
		}
		if (is_get == 2)
		{
			ft_sprintf(&str, "%s, GET_B: OK", str);
			//On envoie le philo dans une fonction qui enleve la reservation des baguettes
			//ft_left_reservation(&(*philo)->next->next);
			//ft_left_reservation(&(*philo)->prev->prev);
			((t_wand*)(*philo)->next->data)->reserved = LEFT;
			((t_wand*)(*philo)->prev->data)->reserved = RIGHT;
			//On peut reserver les deux baguettes
		}
		else
		{
			ft_sprintf(&str, "%s, GET_B: NON_OK", str);
		}
		ft_dprintf(2, "%s%s\n", str, STOP);
		

	//Si une ou plusieurs sont reserver, tester si ce philo a moins de vie,
	//Et si les deux soit disponibles
	//Si oui, alors on lui prends sa reservation
}

enum e_ret_status	ft_can_you_do_eat(t_wand **left, t_wand **right,
							t_philo *data, t_philo_heart **philo)
{
	int				ret_left = 1;
	int				ret_right = 1;

	(void)data;
	ft_reserve_wands(philo);
	//Regarder si les deux sont reserver alors on mange
	//ft_dprintf(2, "%s: RIGHT: %d, LEFT: %d\n",
	//	((t_philo*)(*philo)->data)->name,
	//	left->reserved,
	//	right->reserved
	//);
	if ((*left)->reserved != RIGHT && (*right)->reserved != LEFT)//Si la baguette n est pas reservé
	{
		
	ft_dprintf(2, "%s0CYDE%s (%s) LEFT: [%s], RIGHT: [%s]%s",
		BLUE,
		RED,
		((t_philo*)(*philo)->data)->name,
		(*left)->reserved == 0 ? "NOTHING" : (*left)->reserved == 1 ? "LEFT" : "RIGHT",
		(*right)->reserved == 0 ? "NOTHING" : (*right)->reserved == 1 ? "LEFT" : "RIGHT",
		RED
	);
		//Regarder si elle n'est pas reserver
		ret_left = pthread_mutex_trylock(&((*left)->mutex));
		if (ret_left)
			ret_right = pthread_mutex_trylock(&((*right)->mutex));
		dprintf(2, "%sRET_LEFT: [%d], RET_RIGHT: [%d]%s\n",
			PURPLE,
			ret_left,
			ret_right,
			STOP
		);
	}
	else
	{
		
	ft_dprintf(2, "%s1CYDE%s (%s) LEFT: [%s], RIGHT: [%s]%s\n",
		BLUE,
		GREEN,
		((t_philo*)(*philo)->data)->name,
		(*left)->reserved == 0 ? "NOTHING" : (*left)->reserved == 1 ? "LEFT" : "RIGHT",
		(*right)->reserved == 0 ? "NOTHING" : (*right)->reserved == 1 ? "LEFT" : "RIGHT",
		STOP
	);

		//sleep(200);
		ret_left = pthread_mutex_lock(&(*left)->mutex);
		ret_right = pthread_mutex_lock(&(*right)->mutex);
		//ft_left_reservation(left);
		//ft_left_reservation(right);
		ft_left_reservation(&(*philo)->prev->prev);
		ft_left_reservation(&(*philo)->next->next);
	}
	//sleep(200);
	if (!ret_left && ret_right)
	{
		ft_dprintf(2, "%s1CYDE_RET%s (%s) STATE: [%s], LEFT:[%d], RIGHT:[%d]%s\n",
			CYAN,
			RED,
			((t_philo*)(*philo)->data)->name,
			"THINK",
			ret_left,
			ret_right,
			STOP
		);
		return (LEFT);
	}
	else if (ret_left && !ret_right)
	{
		ft_dprintf(2, "%s1CYDE_RET%s (%s) STATE: [%s], LEFT:[%d], RIGHT:[%d]%s\n",
			CYAN,
			RED,
			((t_philo*)(*philo)->data)->name,
			"THINK",
			ret_left,
			ret_right,
			STOP
		);
		return (RIGHT);
	}
	else if (ret_left && ret_right)
	{
		ft_dprintf(2, "%s1CYDE_RET%s (%s) STATE: [%s], LEFT:[%d], RIGHT:[%d]%s\n",
			CYAN,
			RED,
			((t_philo*)(*philo)->data)->name,
			"NOTHING",
			ret_left,
			ret_right,
			STOP
		);
		return (NOTHING);
	}
	else
	{
		ft_dprintf(2, "%s1CYDE_RET%s (%s) STATE: [%s], LEFT:[%d], RIGHT:[%d]%s\n",
			CYAN,
			GREEN,
			((t_philo*)(*philo)->data)->name,
			"EAT",
			ret_left,
			ret_right,
			STOP
		);
		return (ALL);
	}
}

static size_t		ft_rest_begin_actualize(t_philo_heart **philo,
														t_philo_mother **mother)
{
	char			*str1;
	char			*str;

	((t_philo*)(*philo)->data)->state = TO_REST;
	pthread_mutex_lock(&g_gmutex);
	ft_sprintf(&str1, "%s%s is resting\n", (*mother)->result,
											((t_philo*)(*philo)->data)->name);
	free((*mother)->result);
	(*mother)->result = str1;
	ft_sprintf(&str, "%d", ft_handle_define(GET_INFOS, REST, 0));
	ft_actualize(((t_philo*)(*philo)->data)->capsule, "SE REPOSE", X_STATE,
			Y_STATE);
	ft_actualize(((t_philo*)(*philo)->data)->capsule, str, X_TIME, Y_TIME);
	pthread_mutex_unlock(&g_gmutex);
	ft_strdel(&str);
	return (time(NULL));
}

static void			ft_rest_mid_actualize(t_philo **data,
										t_philo_mother **mother, char *str[], int i, size_t begin_time, size_t now_time, int rest_t, t_philo_heart **philo)
{
	char			*str1;

	pthread_mutex_lock(&g_gmutex);
	if (i % 2 != 0)
	{
		ft_actualize((*data)->capsule, str[0], X_LIFE, Y_LIFE);
		ft_actualize((*data)->capsule, str[1], X_TIME, Y_TIME);
	}
	if (!(*data)->life)
	{
		ft_sprintf(&str1, "%s%s est mort\n", (*mother)->result, (*data)->name);
		(*mother)->all_in_life = false;
		free((*mother)->result);
		(*mother)->result = str1;
	}

	//Quand il reste un demi-seconde on peut reserver la wand
	if (now_time + 1 >= begin_time + rest_t)
		ft_reserve_wands(philo);
	pthread_mutex_unlock(&g_gmutex);
}

int					ft_rest(t_philo_heart **philo, t_philo **data,
														t_philo_mother **mother)
{
	char			*str[2];
	size_t			begin_time;
	size_t			now_time;
	int				rest_t;
	int				i = 0;

	rest_t = ft_handle_define(GET_INFOS, REST, 0);
	str[0] = NULL;
	str[1] = NULL;
	begin_time = ft_rest_begin_actualize(philo, mother);
	now_time = begin_time;
	while (now_time <= begin_time + rest_t && (*mother)->all_in_life)
	{
		usleep(DEMI_SEC);
		//Diviser par deux √
		if (i % 2 != 0)
			(*data)->life = (*data)->life - 1;
		ft_sprintf(&str[0], "%d", (*data)->life);
		time((time_t*)&now_time);
		ft_sprintf(&str[1], "%zi", (int)((rest_t + begin_time) - now_time) > 0 ?
				(rest_t + begin_time) - now_time : 0);
		ft_dprintf(3, "NAME: [%s]\n", (*data)->name);
		ft_rest_mid_actualize(data, mother, str, i, begin_time, now_time, rest_t, philo);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		i++;
	}
	return (0);
}

int					ft_eat_or_think(t_philo_heart **philo, t_philo **data,
														t_philo_mother **mother)
{
	int				ret;

	if ((ret = ft_can_you_do_eat((t_wand**)&(*philo)->prev->data, (t_wand**)&(*philo)->next->data,
					(*philo)->data, philo)) == ALL)
	{
		//sleep(200);
		ft_eat(data, philo, mother);
	}
	else if (ret == LEFT || ret == RIGHT)
	{
		//sleep(200);
		ft_think(ret, philo, data, mother);
	}
	else
	{
		//sleep(200);
		return (1);
	}

		//sleep(200);
	return (0);
}
